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
  m_inputBufferSize = inputBufferSize;

  //Calculate fftSize (should be  a power of 2 higher than the biggest bufferSize)
  m_fftSize = m_inputBufferSize + impulseResponse.size();

  //a<<=b is the same as a*=(2^b)
  int a = 1;
  while (a < m_fftSize)
  {
    a <<= 1;
  }
  m_fftSize = a;

  //Initialise all buffers
  m_inputBuffer.resize(m_fftSize, 0);
  m_impulseResponse.resize(m_fftSize, 0);
  m_overlappingBuffer.resize(m_fftSize*2, 0);
  m_outputBuffer.resize(inputBufferSize);
  m_tail.resize(impulseResponse.size());

  //FFT and copy to m_impulseResponse


  memcpy(&m_impulseResponse[0], &impulseResponse[0], impulseResponse.size() * sizeof(float));
  realfft_packed(&m_impulseResponse[0], m_fftSize);
}


vector<float> ConvolutionEngine::process(vector<float>& input)
{
  //FFT and copy to input to own inputBuffer
  memcpy(&m_inputBuffer[0], &input[0], input.size() * sizeof(float));
  realfft_packed(&m_inputBuffer[0], m_fftSize);


//==============================CONVOLUTION=================================
  //0 Hz
  m_overlappingBuffer[0] = m_inputBuffer[0] * m_impulseResponse[0];
  //[0 Hz, Nyquist]
  for (int i = 2; i < m_fftSize; i+=2) {
    std::complex z1(m_inputBuffer[i], m_inputBuffer[i+1]);
    std::complex z2(m_impulseResponse[i], m_impulseResponse[i+1]);

    std::complex z = z1*z2;
    m_overlappingBuffer[i] = real(z);
    m_overlappingBuffer[i+1] = imag(z);
  }
  //Nyquist
  m_overlappingBuffer[1] = m_inputBuffer[1] * m_impulseResponse[1];

//==================================END CONVOLUTION==================================


  //inverse fft the overlapping buffer to get audio again
  irealfft_packed(&m_overlappingBuffer[0], m_fftSize);

  //Copy the designated part to m_outputBuffer
  memcpy(&m_outputBuffer[0], &m_overlappingBuffer[0], m_inputBufferSize * sizeof(float));

  //TODO - tail kan langer zijn dan outputbuffer
  //FIXME - outputbufferSize is niet fftSize
  //add tail to m_outputBuffer and normalise
  for (int i = 0; i < m_outputBuffer.size(); i++)
  {
    if (i < m_tail.size())
    {
      m_outputBuffer[i] += m_tail[i]; //TODO - the sound is not there when this is disabled
    }
    //Normalising
    m_outputBuffer[i] *= m_fftSize; //TODO - this doesnt have to be here?
  }

  //copy new tail to m_tail
  memcpy(&m_tail[0], &m_overlappingBuffer[m_inputBufferSize], m_tail.size() * sizeof(float)); //FIXME - pping buffer

  //clear overlapping buffer for next use
  m_overlappingBuffer.clear();
  m_overlappingBuffer.assign(m_fftSize*2, 0);

  return m_outputBuffer;
}

