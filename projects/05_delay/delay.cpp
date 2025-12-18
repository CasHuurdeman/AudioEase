//
// Created by cashu on 04/11/2025.
//

#include "delay.h"
#include <iostream>
#include "dspMath.h"

Delay::Delay(float samplesDelay, float feedback)
{
    // std::cout << "Delay - constructor" << std::endl;
    m_feedback = feedback;
    m_circularBuffer = new CircularBuffer(samplesDelay);
}

Delay::Delay(float samplesDelay, float feedback, int bufferSize)
{
    // std::cout << "Delay - constructor" << std::endl;
    m_feedback = feedback;
    m_circularBuffer = new CircularBuffer(samplesDelay, bufferSize);
}

Delay::~Delay()
{
    // std::cout << "Delay - destructor" << std::endl;
    delete m_circularBuffer;
    m_circularBuffer = nullptr;
};

float Delay::process(float input)
{
    //Bypass
    if (m_bypassOn) { return input; }

    // float s = signal.sine(1, 48000);
    //  m_circularBuffer->setSamplesDelay(dspMath::msToSamples(10, 48000) + dspMath::msToSamples(s * 6, 48000));

    float output = m_circularBuffer->read();
    m_circularBuffer->write(output * m_feedback + input);
    return output;
}

void Delay::setFeedback(float feedback)
{
    if (feedback >= 1 || feedback <= 1)
    {
    m_feedback = feedback;
    }
    else
    {
        std::cout << "Delay::setFeedback; Error: feedback out of range <0,1>" << std::endl;
    }
}

void Delay::setSamplesDelay(float samplesDelay)
{
    m_circularBuffer->setSamplesDelay(samplesDelay);
}

void Delay::setBypass(bool bypassOn)
{
    m_bypassOn = bypassOn;
}