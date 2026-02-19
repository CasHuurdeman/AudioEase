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
    if (m_normalise)    normalise = 1 / m_room.getReceiver(channel)->getSourceAmplitude()[0];

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

         float prevAmp = m_room.getReceiver(channel)->getSourceAmplitude()[i];
         float targetAmp = m_room.getReceiver(channel)->getReflections()[i][1];

         float amp = Smoothe::smootheValue(prevAmp, targetAmp, numSamplesLeft);
         m_room.getReceiver(channel)->setSourceAmplitude(i, amp);
         }

        //If m_normalise = true: normalising the first reflection to input level and the rest with it
        output += m_buffers[channel]->read(i) * m_room.getReceiver(channel)->getSourceAmplitude()[i] * normalise;
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
        reloadRoom();
    }
}

void ReflectionManager::changeRoomDimensions(float X, float Y, float Z)
{
    m_room.setRoomDimensions(X,Y,Z);
    reloadRoom();
}


void ReflectionManager::turnOffDirectSound(float dimfactor)
{
    //because we only want to dim, not amp
    if (dimfactor < 1) dimfactor = 1;

    for(int i = 0; i < m_numChannels; i++)
    {
        if (m_directSoundOn) m_directSound.push_back(m_room.getReceiver(i)->getReflections()[0][1]);
        m_room.getReceiver(i)->getReflections()[0][1] = m_directSound[i] / dimfactor;
    }
    m_directSoundOn = false;
}

void ReflectionManager::turnOnDirectSound()
{
    if (!m_directSoundOn)
    {
        for(int i = 0; i < m_numChannels; i++)
        {
            m_room.getReceiver(i)->getReflections()[0][1] = m_directSound[i];
        }
        m_directSound.clear();
    }
    m_directSoundOn = true;
}

void ReflectionManager::turnOnZaxis(bool ZaxisOn)
{
    m_room.setZaxisOn(ZaxisOn);
    reloadRoom();
}

void ReflectionManager::reloadRoom()
{
    m_room.calculateMirrorSources();
    m_room.calcReflectionsForAllReceivers();
    updateDelays();
}

