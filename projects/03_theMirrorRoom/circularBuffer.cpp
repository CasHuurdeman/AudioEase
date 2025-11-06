//
// Created by cashu on 04/11/2025.
// only works within the JUCE framework
//

#include "circularBuffer.h"
#include <iostream>
#include "interpolation.h"

//=========================CONSTRUCTORS AND DESTRUCTORS=====================
CircularBuffer::CircularBuffer(float samplesDelay)
{
  std::cout << "CircularBuffer - constructor" << std::endl;

    m_samplesDelay = samplesDelay;
    m_bufferSize = ceil(samplesDelay);

    //Allocate memory for m_buffer
    m_buffer = new float[m_bufferSize];
	for (int i = 0; i < m_bufferSize; i++)
    {
        m_buffer[i] = 0;
    }

    initReadHead();
}

CircularBuffer::CircularBuffer(float samplesDelay, int bufferSize)
{
	std::cout << "CircularBuffer - constructor" << std::endl;
        
    m_samplesDelay = samplesDelay;
    m_bufferSize = bufferSize;

    //Allocate memory for m_buffer
    m_buffer = new float[bufferSize];
	for (int i = 0; i < bufferSize; i++)
    {
        m_buffer[i] = 0;
    }

    initReadHead();
}

CircularBuffer::~CircularBuffer()
{
	std::cout << "CircularBuffer - destructor" << std::endl;
    delete [] m_buffer;
    m_buffer = nullptr;
}

//========================================================================
//the read is sample based so the delay can be time-varying
float CircularBuffer::read()
{
	int value = m_buffer[m_readHead];
    m_readHead++;
    wrap(m_readHead);

    int nextValue = m_buffer[m_readHead];

    float output = Interpolation::linMap(m_sampleOffset, value, nextValue);
    return output;
}


//This write function writes inputBuffers away to a circularBuffer with memcpy
// because of memcpy we need to check how much space we have left before the end of the buffer
// if there is not enough space left, we first write what we can, after that put writeHead on 0 and write the rest away
void CircularBuffer::write(juce::AudioBuffer<float> inputBuffer)
{
   int bufferIndexesLeft = m_bufferSize - m_writeHead;
   int inputBufferNumSamples = inputBuffer.getNumSamples();

   if(inputBuffer.getNumSamples() < bufferIndexesLeft)
   {
     std::memcpy(&m_buffer[m_writeHead], inputBuffer.getReadPointer(0), inputBufferNumSamples * sizeof(float));
     m_writeHead += inputBufferNumSamples;
   }
   else
   {
   	 int samplesLeftToWrite = inputBufferNumSamples - bufferIndexesLeft;

     std::memcpy(&m_buffer[m_writeHead], inputBuffer.getReadPointer(0), bufferIndexesLeft * sizeof(float));
     //the writeHead should be on 0 now
     m_writeHead = 0;
     std::memcpy(&m_buffer[m_writeHead], inputBuffer.getReadPointer(0, bufferIndexesLeft), samplesLeftToWrite * sizeof(float));
     m_writeHead = samplesLeftToWrite;
   }
}

void CircularBuffer::wrap(int& head)
{
    if (head >= m_bufferSize)
  	{
       	 head -= m_bufferSize;
   	}
}

void CircularBuffer::initReadHead()
{
  	if(m_samplesDelay > m_bufferSize)
  	{
          std::cout << "CircularBuffer::initReadHead; Error: samplesDelay is bigger than bufferSize" << std::endl;
  	}
    else
    {
        m_readHead = m_writeHead - static_cast<int>(m_samplesDelay) + m_bufferSize;
        m_sampleOffset = m_samplesDelay - m_readHead;
    	//readHead gets changed--> so wrap
        wrap(m_readHead);
    }
}

//==================================SETTERS=====================================
void CircularBuffer::setSamplesDelay(float samplesDelay)
{
  	if(samplesDelay > m_bufferSize)
  	{
          std::cout << "CircularBuffer::setSamplesDelay; Error: samplesDelay is bigger than bufferSize" << std::endl;
  	}
    else
    {
        m_samplesDelay = samplesDelay;
        initReadHead();
    }
}