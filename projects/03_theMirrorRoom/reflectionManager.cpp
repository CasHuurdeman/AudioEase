//
// Created by cashu on 13/11/2025.
//

// in room.cpp and receiver.cpp too

#include "reflectionManager.h"
#include <iostream>
// #include "tappedDelay.h"
#include "customPrint.h"
#include "dspMath.h"

//TODO - als ik er nu twee aanroep worden dezelfde dingen ook twee keer berekend. Dit is in pricipe niet erg straks als ik met twee oren/speakers ga werken, tenzij ik dat in de class zelf wil regelen
// --> GEEF EEN POINTER VAN ROOM MEE IN DE CONSTRUCTOR
ReflectionManager::ReflectionManager()
{
    std::cout << "ReflectionManager - constructor" << std::endl;
}

ReflectionManager::~ReflectionManager()
{
    std::cout << "ReflectionManager - destructor" << std::endl;
}

void ReflectionManager::prepare(int sampleRate, int numChannels) {
    m_numChannels = numChannels;
    m_sampleRate = sampleRate;
    m_room.prepare(numChannels);
    createDelays();
}


float ReflectionManager::process(float input, int channel)
{
    if(m_bypassOn){ return input; }

    float output = 0;
    for(int i = 0; i < m_room.getReceiver(channel)->getNumReflections(); i++)
    {
    // /room.getSourceAmplitude -> To normalise the reflections for the input
    // (the same effect as input * room.getSourceAmplitude() and then gaining everything up)
    const float normalise = 1 / m_room.getReceiver(channel)->getSourceAmplitude();
    output += m_buffers[channel]->read(i) * m_room.getReceiver(channel)->getReflections()[i][1] * normalise;
    }
    m_buffers[channel]->write(output * m_feedback + input);

    return output;
}

void ReflectionManager::createDelays()
{
    m_buffers.resize(m_numChannels);
    for (int channel = 0; channel < m_numChannels; channel++)
    {
        float samplesDelay = dspMath::msToSamples(m_room.getMaxDelay(), m_sampleRate);
        m_buffers[channel] = new CircularBuffer(static_cast<int>(ceil(samplesDelay)));

        for(int i = 0; i < m_room.getReceiver(channel)->getNumReflections(); i++)
        {
            samplesDelay = dspMath::msToSamples(m_room.getReceiver(channel)->getReflections()[i][0], m_sampleRate);
            m_buffers[channel]->addReadHead(samplesDelay);
        }
    }
}

void ReflectionManager::setBypass(bool bypassOn)
{
    m_bypassOn = bypassOn;
}