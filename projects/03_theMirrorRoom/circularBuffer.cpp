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
  // std::cout << "CircularBuffer - constructor(int bufferSize)" << std::endl;

	//The plus one is so that calling write before read doesn't matter anymore, so not necessarily needed
    m_bufferSize = bufferSize;

    //Allocate memory for m_buffer
    m_buffer = new float[m_bufferSize];
	for (int i = 0; i < m_bufferSize; i++)
    {
        m_buffer[i] = 0;
    }
}

CircularBuffer::CircularBuffer(float samplesDelay, int bufferSize)
{
	// std::cout << "CircularBuffer - constructor(float samplesDelay, int bufferSize)" << std::endl;

    m_bufferSize = bufferSize;

    //Allocate memory for m_buffer
    m_buffer = new float[bufferSize];
	for (int i = 0; i < bufferSize; i++)
    {
        m_buffer[i] = 0;
    }

    addReadHead(samplesDelay);
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

	//store value and increment readHead to nextvalue
	float value = m_buffer[intReadHead];
    wrap(++m_readHeads[readHeadIndex]);

	//reset intReadHead and read nextValue
	intReadHead = m_readHeads[readHeadIndex];
    float nextValue = m_buffer[intReadHead];

	//calculate the output with interpolation
	float output = Interpolation::linMap(sampleOffset, value, nextValue);

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
  m_samplesDelay.push_back({samplesDelay,samplesDelay});

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
    	m_samplesDelay[readHeadIndex][0] = samplesDelay;
        initReadHead(m_readHeads[readHeadIndex], samplesDelay);
    }
}


void CircularBuffer::setTargetSamplesDelay(int readHeadIndex, float samplesDelay) {
	if (samplesDelay > m_bufferSize) std::cerr << "TappedDelay::setTargetSamplesDelay - samplesDelay cant be bigger than bufferSize" << std::endl;
	else
	{
		m_samplesDelay[readHeadIndex][1] = samplesDelay;
	}
}


void CircularBuffer::removeReadHead(int readHeadIndex) {
	if (readHeadIndex < m_readHeads.size())
	{
		std::cout << "CircularBuffer::removeReadHead; Error: This index doest exist" << std::endl;
	}
	m_readHeads.erase(m_readHeads.begin() + readHeadIndex);
	m_samplesDelay.erase(m_samplesDelay.begin() + readHeadIndex);
}