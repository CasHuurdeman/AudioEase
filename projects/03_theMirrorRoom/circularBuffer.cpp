//
// Created by cashu on 04/11/2025.
// only works within the JUCE framework
//

#include "circularBuffer.h"
#include <iostream>
#include "interpolation.h"

//=========================CONSTRUCTORS AND DESTRUCTORS=====================
CircularBuffer::CircularBuffer(int bufferSize)
{
  std::cout << "CircularBuffer - constructor(int bufferSize)" << std::endl;

	//The plus one is so that calling write before read doesn't matter anymore, so not necessarily needed
    m_bufferSize = bufferSize;

    //Allocate memory for m_buffer
    m_buffer = new float[m_bufferSize];
	for (int i = 0; i < m_bufferSize; i++)
    {
        m_buffer[i] = 0;
    }
	m_readHeads.clear();
}

CircularBuffer::CircularBuffer(float samplesDelay, int bufferSize)
{
	std::cout << "CircularBuffer - constructor(float samplesDelay, int bufferSize)" << std::endl;

    m_bufferSize = bufferSize;

    //Allocate memory for m_buffer
    m_buffer = new float[bufferSize];
	for (int i = 0; i < bufferSize; i++)
    {
        m_buffer[i] = 0;
    }

    initReadHead(m_readHeads[0], samplesDelay);
}

CircularBuffer::~CircularBuffer()
{
	// std::cout << "CircularBuffer - destructor" << std::endl;
    delete [] m_buffer;
    m_buffer = nullptr;
}

//========================================================================
//the read is sample based so the delay can be time-varying
float CircularBuffer::read(int readHeadIndex)
{
    float p;
	float sampleOffset = modf(m_readHeads[readHeadIndex], &p);
    int intReadHead = static_cast<int>(p);

	float value = m_buffer[intReadHead];
    wrap(++m_readHeads[readHeadIndex]);

	intReadHead = m_readHeads[readHeadIndex];
    float nextValue = m_buffer[intReadHead];

	float output = Interpolation::linMap(sampleOffset, value, nextValue);
	// std::cout << "ReadHead" << readHeadIndex << ": " << m_readHeads[readHeadIndex] << "\nValue: " << value << " nextValue: " << nextValue << " output: " << output << " sampleOffset: " << sampleOffset << "\n" << std::endl;
    return output;
}


//write function
void CircularBuffer::write(float input)
{
    m_buffer[m_writeHead] = input;
	wrap(++m_writeHead);
}

void CircularBuffer::wrap(auto& head)
{
    if (head >= m_bufferSize)
  	{
       	 head -= m_bufferSize;
   	}
}

void CircularBuffer::initReadHead(float& readHead, float samplesDelay)
{
  	if(samplesDelay > static_cast<float>(m_bufferSize))
  	{
          std::cout << "CircularBuffer::initReadHead; Error: samplesDelay is bigger than bufferSize" << std::endl;
  	}
    else
    {
        readHead = static_cast<float>(m_writeHead) - samplesDelay + static_cast<float>(m_bufferSize);
    	//readHead gets changed--> so wrap
        wrap(readHead);
    }
}

//For tapped delay
void CircularBuffer::addReadHead(float samplesDelay)
{
  float readHead = 0.0f;
  initReadHead(readHead, samplesDelay);
  m_readHeads.push_back(readHead);
}


//==================================SETTERS=====================================
void CircularBuffer::setSamplesDelay(int readHeadIndex, float samplesDelay)
{
  	if(samplesDelay > static_cast<float>(m_bufferSize))
  	{
          std::cout << "CircularBuffer::setSamplesDelay; Error: samplesDelay is bigger than bufferSize" << std::endl;
  	}
    else
    {
        initReadHead(m_readHeads[readHeadIndex], samplesDelay);
    }
}

std::vector<float> CircularBuffer::getSamplesDelay()
{
  std::vector<float> samplesDelay;
  for(float readHead : m_readHeads)
  {
    float delay = static_cast<float>(m_writeHead) - readHead + static_cast<float>(m_bufferSize);
  	wrap(delay);
    samplesDelay.push_back(delay);
  }
  return samplesDelay;
}

void CircularBuffer::removeReadHead(int readHeadIndex)
{
	if (readHeadIndex < m_readHeads.size())
	{
		std::cout << "CircularBuffer::removeReadHead; Error: This index doest exist" << std::endl;
	}
	m_readHeads.erase(m_readHeads.begin() + readHeadIndex);
}