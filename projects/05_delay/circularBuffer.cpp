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
  // std::cout << "CircularBuffer - constructor" << std::endl;

	//The plus one is so that calling write before read doesn't matter anymore, so not necessarily needed
    m_bufferSize = static_cast<int>(ceil(samplesDelay)) + 1;
    m_samplesDelay = samplesDelay;

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
	// std::cout << "CircularBuffer - constructor" << std::endl;
        
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
	float p;
	float sampleOffset = modf(m_readHead, &p);
	int intReadHead = static_cast<int>(p);

	float value = m_buffer[intReadHead];
	// m_readHeads[readHeadIndex] += m_readSpeed[readHeadIndex];
	wrap(++m_readHead);

	intReadHead = m_readHead;
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

void CircularBuffer::initReadHead()
{
  	if(m_samplesDelay > m_bufferSize)
  	{
  		std::cout << "CircularBuffer::initReadHead; Error: samplesDelay is bigger than bufferSize" << std::endl;
  	}
	else
    {
        m_readHead = static_cast<float>(m_writeHead) - m_samplesDelay + static_cast<float>(m_bufferSize);
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