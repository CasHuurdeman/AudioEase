//
// Created by cashu on 08/01/2026.
//

#include "convolutionEngine.h"
#include <iostream>
#include <complex>
#include "FFT.h"

ConvolutionEngine::ConvolutionEngine()
{
  std::cout << "ConvolutionEngine - constructor" << std::endl;
}

ConvolutionEngine::~ConvolutionEngine()
{
  std::cout << "ConvolutionEngine - destructor" << std::endl;
}

void ConvolutionEngine::prepare(int inputBufferSize, vector<float>& impulseResponse)
{

//find fftSize
  m_fftSize = m_inputBufferSize = inputBufferSize;
  // m_fftSize = m_inputBufferSize = 8;

  //a<<=b is the same as a*=(2^b)
  int a = 1;
  while (a < m_fftSize)
  {
    a <<= 1;
  }
  m_fftSize = a;

//In how many buffers do I want to cut the fft
// --> I dont need to physically cut it up, because all the fft's are in place

  //size of m_impulseResponse needs to be a multiple of m_fftSize
  m_IRSize = impulseResponse.size();
  //x is how many times m_fftSize fits in impulseResponse
  float numIRs = static_cast<float>(m_IRSize)/static_cast<float>(m_fftSize);
  m_numIRs = ceil(numIRs);
  m_IRSize = m_numIRs * m_fftSize;

  m_impulseResponse.resize(m_IRSize, 0);
  memcpy(&m_impulseResponse[0], &impulseResponse[0], impulseResponse.size() * sizeof(float));

  for(int i = 0; i < m_numIRs; i++)
  {
    int x = i * m_fftSize;
    realfft_packed(&m_impulseResponse[x], m_fftSize);
  }

  //Initialise all buffers
  m_inputBuffer.resize(m_IRSize, 0);
}


vector<float> ConvolutionEngine::process(vector<float>& input)
{
  m_outputBuffer.clear();
  m_outputBuffer.resize(m_inputBufferSize, 0);

  writeToBuffer(input);


//FIXME - inputbuffersize != fftSize --> later
  if (m_inputBufferSize != m_fftSize) std::cout << "ConvolutionEngine::process - ERROR" << std::endl;

  vector<float> buffer(m_fftSize);
  for(int i = 0; i < m_numIRs; i++)
  {
      memcpy(&buffer[0], &m_inputBuffer[m_readHead], m_fftSize * sizeof(float));
      m_readHead += m_fftSize;
      wrap(m_readHead);
      realfft_packed(&buffer[0], m_fftSize);

      convolve(buffer);
  }

  //inverse fft the overlapping buffer to get audio again
  irealfft_packed(&m_outputBuffer[0], m_fftSize);

    //Normalising
  for (int i = 0; i < m_outputBuffer.size(); i++)
  {
    m_outputBuffer[i] *= m_fftSize; //TODO - this doesnt have to be here?
  }

  return m_outputBuffer;
}


void ConvolutionEngine::convolve(vector<float>& buffer)
{
  //0 Hz
  m_outputBuffer[0] += buffer[0] * m_impulseResponse[0];
  //[0 Hz, Nyquist]
  for (int i = 2; i < m_fftSize; i+=2) {
    std::complex z1(buffer[i], buffer[i+1]);
    std::complex z2(m_impulseResponse[i], m_impulseResponse[i+1]);

    std::complex z = z1*z2;
    m_outputBuffer[i] += real(z);
    m_outputBuffer[i+1] += imag(z);
  }
  //Nyquist
  m_outputBuffer[1] *= buffer[1] * m_impulseResponse[1];
}


void ConvolutionEngine::writeToBuffer(vector<float>& input)
{
    memcpy(&m_inputBuffer[m_writeHead], &input[0], m_inputBufferSize * sizeof(float));
    m_writeHead += m_fftSize;
    wrap(m_writeHead);
}

void ConvolutionEngine::wrap(int& head)
{
  if (head >= m_IRSize)
  {
    head -= m_IRSize;
  }
}


//void ConvolutionEngine::writeToBuffer(vector<float>& input)
//{
//  if(m_inputBufferSize <= m_IRSize - m_writeHead)
//  {
//    memcpy(&m_inputBuffer[m_writeHead], &input[0], m_inputBufferSize * sizeof(float));
//    m_writeHead += m_inputBufferSize;
//    wrap(m_writeHead);
//  }
//  else
//  {
//     int x = m_IRSize - m_writeHead;
//     int y = m_inputBufferSize - x;
//
//    memcpy(&m_inputBuffer[m_writeHead], &input[0], x * sizeof(float));
//    m_writeHead += x; //should be 0
//    wrap(m_writeHead);
//    memcpy(&m_inputBuffer[m_writeHead], &input[x], y * sizeof(float));
//    m_writeHead = y;
//  }
//}

