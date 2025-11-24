//
// Created by cashu on 04/11/2025.
//

#include "tappedDelay.h"
#include <iostream>

TappedDelay::TappedDelay(float samplesDelay)
{
    m_circularBuffer = new CircularBuffer(samplesDelay);
}

TappedDelay::TappedDelay(float samplesDelay, float feedback)
{
    m_feedback = feedback;
    m_circularBuffer = new CircularBuffer(samplesDelay);
}

TappedDelay::TappedDelay(float samplesDelay, float feedback, int bufferSize)
{
    m_feedback = feedback;
    m_circularBuffer = new CircularBuffer(samplesDelay, bufferSize);
}

TappedDelay::~TappedDelay()
{
    delete m_circularBuffer;
    m_circularBuffer = nullptr;
};

float TappedDelay::process(float input)
{
    //TODO - somewhere here needs to be an insert for low pas filtering.
    //Bypass
    if (m_bypassOn == true) { return input; }
    float output = 0;
    for (int i = 0; i < m_circularBuffer->getNumReadHeads(); i++)
    {
        output += m_circularBuffer->read(i);
    }
    m_circularBuffer->write(output * m_feedback + input);
    return output;
}

void TappedDelay::setFeedback(float feedback)
{
    if (0.0f <= feedback <= 1.0f)
    {
    m_feedback = feedback;
    }
    else
    {
        std::cout << "TappedDelay::setFeedback; Error: feedback out of range <0,1>" << std::endl;
    }
}

void TappedDelay::setSamplesDelay(int readHeadIndex, float samplesDelay)
{
    m_circularBuffer->setSamplesDelay(readHeadIndex, samplesDelay);
}

void TappedDelay::setBypass(bool bypassOn)
{
    m_bypassOn = bypassOn;
}
