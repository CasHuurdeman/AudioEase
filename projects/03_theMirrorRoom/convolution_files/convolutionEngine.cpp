//
// Created by cashu on 08/01/2026.
//

#include "convolutionEngine.h"
#include <iostream>
#include <complex>
#include "FFT.h"
#include "writeToFile.h"

std::string sourcePath = SOURCE_DIR;

ConvolutionEngine::ConvolutionEngine()
{
  std::cout << "ConvolutionEngine - constructor" << std::endl;
}

ConvolutionEngine::~ConvolutionEngine()
{
  std::cout << "ConvolutionEngine - destructor" << std::endl;
}

void ConvolutionEngine::prepare(const int inputBufferSize, vector<float>& impulseResponse)
{
  m_IR = impulseResponse;

//find fftSize
  m_dataBlockSize = inputBufferSize;
  m_fftSize = m_dataBlockSize * 2;

  //a<<=b is the same as a*=(2^b)
  int a = 1;
  while (a < m_fftSize)
  {
    a <<= 1;
  }
  m_fftSize = a;

//In how many buffers do I want to cut the fft
// --> I dont need to physically cut it up, because all the fft's are in place

  //size of m_impulseResponseFFT needs to be a multiple of m_fftSize
  m_IRSize = m_IR.size();
  //x is how many times m_fftSize fits in impulseResponse
  float numIRs = static_cast<float>(m_IRSize)/static_cast<float>(m_dataBlockSize);
  m_numIRs = ceil(numIRs);
  m_IRSize = m_numIRs * m_fftSize;

  //Make sure that impulseResponse will be broken up nicely in parts of m_dataBlockSize
  while (m_IR.size() < m_numIRs * m_dataBlockSize)
  {
    m_IR.push_back(0);
  }

  //=====================
  fftIR();

  //Initialise all buffers
  m_inputBuffer.resize(m_IRSize, 0);
  m_overlappingBuffer.resize(m_fftSize, 0);

  if (m_dataBlockSize*2 != m_fftSize) std::cout << "ConvolutionEngine::process - ERROR, inputLength should be 2^x" << std::endl;
}


vector<float> ConvolutionEngine::process(vector<float>& input)
{

//=================================OVERLAP-SAVE=================================
  vector<float> outputBuffer(m_dataBlockSize);

  // Copy  and normalise the reverbtail of the previous convolution to the outputbuffer
   for (int i = 0; i < m_dataBlockSize; i++)
   {
     outputBuffer[i] = m_overlappingBuffer[m_dataBlockSize + i] * m_fftSize;
   }
  m_overlappingBuffer.clear();
  m_overlappingBuffer.resize(m_fftSize, 0);
//=============================================================================


//================================CONVOLUTION===================================
  writeToBufferAndFFT(input);

  for(int i = 0; i < m_numIRs; i++)
  {
      convolve();
  }

  //To start convolution at the right spot next loop
  m_readHeadInput = m_writeHead;
  wrap(m_readHeadInput);

  //inverse fft the overlapping buffer to get audio again
  irealfft_packed(&m_overlappingBuffer[0], m_fftSize);
//=============================================================================


//=================================OVERLAP-SAVE=================================
  //Normalising and overlap-add
  for (int i = 0; i < m_dataBlockSize; i++)
  {
    outputBuffer[i] += m_overlappingBuffer[i] * m_fftSize;
  }

  return outputBuffer;
//=============================================================================
}


void ConvolutionEngine::convolve()
{

  //0 Hz
  m_overlappingBuffer[0] += m_inputBuffer[m_readHeadInput] * m_impulseResponseFFT[m_readHeadIR];
  //[0 Hz, Nyquist]
  for (int i = 2; i < m_fftSize; i+=2) {
    std::complex z1(m_inputBuffer[m_readHeadInput +i], m_inputBuffer[m_readHeadInput + i+1]);
    std::complex z2(m_impulseResponseFFT[m_readHeadIR + i], m_impulseResponseFFT[m_readHeadIR + i+1]);

    std::complex z = z1*z2;
    m_overlappingBuffer[i] += real(z);
    m_overlappingBuffer[i+1] += imag(z);
  }
  //Nyquist
  m_overlappingBuffer[1] += m_inputBuffer[m_readHeadInput + 1] * m_impulseResponseFFT[m_readHeadIR + 1];


//To see which part to convolve
  m_readHeadInput += m_fftSize;
  wrap(m_readHeadInput);
  m_readHeadIR -= m_fftSize;
  wrap(m_readHeadIR);
}


void ConvolutionEngine::writeToBufferAndFFT(vector<float>& input)
{
//copy  input
    memcpy(&m_inputBuffer[m_writeHead], &input[0], m_dataBlockSize * sizeof(float));

//Make sure the zero-padding after the dataBlock is there
    int beginPos = m_writeHead + m_dataBlockSize;
    int endPos = m_writeHead + m_dataBlockSize*2;
    fill(m_inputBuffer.begin() + beginPos, m_inputBuffer.begin() + endPos, 0);

//FFT
    realfft_packed(&m_inputBuffer[m_writeHead], m_fftSize);

//inc head
    m_writeHead += m_fftSize;
    wrap(m_writeHead);
}


void ConvolutionEngine::wrap(int& head)
{
  if (head >= m_IRSize) head -= m_IRSize;
  else if (head < 0) head += m_IRSize;
}

//TODO - can be optimised
void ConvolutionEngine::cutEarlyReflections(int numSamples)
{
//Put reflections back before cutting
  int size = m_savedEarlyReflections.size();
  if (size > 0)
  {
    memcpy(&m_IR[0], &m_savedEarlyReflections[0], size * sizeof(float));
    m_savedEarlyReflections.clear();
  }


//cut reflections
  for (int i = 0; i < numSamples; i++)
  {
    m_savedEarlyReflections.push_back(m_IR[i]);
    m_IR[i] = 0;
  }

  fftIR();
}

void ConvolutionEngine::fftIR() {
  m_impulseResponseFFT.clear();
  m_impulseResponseFFT.resize(m_IRSize, 0);

  for(int i = 0; i < m_numIRs; i++)
  {
    int x = i * m_fftSize;
    int y = i * m_dataBlockSize;
    memcpy(&m_impulseResponseFFT[x], &m_IR[y], m_dataBlockSize * sizeof(float));

    realfft_packed(&m_impulseResponseFFT[x], m_fftSize);
  }
}

