//
// Created by cashu on 13/11/2025.
//

#include "reflectionManager.h"
#include <iostream>
#include "dspMath.h"
#include "smoothe.h"

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
    // moved to room constructor
    // m_room.changeReceivers(0.17f);

    createDelays();
}

//TODO - dit moet sneller
float ReflectionManager::process(float input, int channel, int numSamplesLeft)
{
    //========================BYPASS===================================
    if(m_bypassOn){ return input; }

    //=========================DELAY===================================
    float output = 0;

    float normalise = 1;
    if (m_normalise)    normalise = 1 / m_room.getReceiver(channel)->getSourceAmplitude();

    for(int i = 0; i < m_room.getReceiver(channel)->getNumReflections(); i++)
    {
        // INTERPOLATION
        //TODO - Declarations out of loop? --> more efficient?
         array<float, 2> samplesDelay = m_buffers[channel]->getSamplesDelay()[i];
         float prevDelay = samplesDelay[0];
         float targetDelay = samplesDelay[1];

         if (prevDelay != targetDelay)
         {
         float delay = Smoothe::smootheValue(prevDelay, targetDelay, numSamplesLeft);
         m_buffers[channel]->setSamplesDelay(i,delay);
         }

        //If m_normalise = true: normalising the first reflection to input level and the rest with it
        output += m_buffers[channel]->read(i) * m_room.getReceiver(channel)->getReflections()[i][1] * normalise;
    }

    m_buffers[channel]->write(output * m_feedback + input);

    return output;
}

void ReflectionManager::createDelays()
{
    //clear m_buffers
        for (int i = 0; i < m_buffers.size(); i++) {
            delete m_buffers[i];
            m_buffers[i] = nullptr;
        }

        m_buffers.clear();

    m_buffers.resize(m_numChannels);
    for (int channel = 0; channel < m_numChannels; channel++)
    {
        //Set the max delay
        float samplesDelay = dspMath::msToSamples(m_room.getMaxDelay(), m_sampleRate);
        m_buffers[channel] = new CircularBuffer(static_cast<int>(ceil(samplesDelay)));

        for(int i = 0; i < m_room.getReceiver(channel)->getNumReflections(); i++)
        {
            samplesDelay = dspMath::msToSamples(m_room.getReceiver(channel)->getReflections()[i][0], m_sampleRate);
            m_buffers[channel]->addReadHead(samplesDelay);
        }
    }
}

void ReflectionManager::updateDelays()
{
    for (int channel = 0; channel < m_numChannels; channel++)
    {
        for(int i = 0; i < m_room.getReceiver(channel)->getNumReflections(); i++)
        {
            float samplesDelay = dspMath::msToSamples(m_room.getReceiver(channel)->getReflections()[i][0], m_sampleRate);
            m_buffers[channel]->setTargetSamplesDelay(i,samplesDelay);
        }
    }
}

void ReflectionManager::moveSource(float X, float Y, float Z)
{
    //check if there's a change
    if (m_room.getSource()[0] != X || m_room.getSource()[1] != Y || m_room.getSource()[2] != Z)
    {
        m_room.setSource(X, Y, Z);

        m_room.calculateMirrorSources();
        //this also calculates the reflections, so this name is a bit unclear maybe
        m_room.updateReceivers();
        updateDelays();
    }
}

