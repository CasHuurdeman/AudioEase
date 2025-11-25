//
// Created by cashu on 13/11/2025.
//

// in room.cpp and receiver.cpp too
#define SOURCE_SEPERATED  0

#include "reflectionManager.h"
#include <iostream>
#include "tappedDelay.h"
//TODO - als ik er nu twee aanroep worden dezelfde dingen ook twee keer berekend. Dit is in pricipe niet erg straks als ik met twee oren/speakers ga werken, tenzij ik dat in de class zelf wil regelen
// --> GEEF EEN POINTER VAN ROOM MEE IN DE CONSTRUCTOR
ReflectionManager::ReflectionManager()
{
    std::cout << "ReflectionManager - constructor" << std::endl;
    createDelays();
}

ReflectionManager::~ReflectionManager()
{
    std::cout << "ReflectionManager - destructor" << std::endl;
}

//TODO - PUT CHANNEL LOOP HERE OR CHANNEL IN FUNCTION CALL
float ReflectionManager::process(float input)
{
    if(m_bypassOn){ return input; }

    float output = 0;
    for(int i = 0; i < m_room.getReceiver(0)->getNumReflections(); i++)
    {
        // /room.getSourceAmplitude -> To normalise the reflections for the input
        // (the same effect as input * room.getSourceAmplitude() and then gaining everything up)
        const float normalise = 1 / m_room.getReceiver(0)->getSourceAmplitude() * static_cast<int>(m_normalised);
        output += m_delays[i]->process(input) * m_room.getReceiver(0)->getReflections()[i][1] * normalise;
    }

    return output;
}

//TODO - start with biggest delay, after that make smaller delays
//TODO - ALSO NEEDS TO BE PER CHANNEL!!!!!
//FIXME VECTOR UBSCRIPT OUT OF RANGE
void ReflectionManager::createDelays()
{
    m_delays.resize(m_room.getReceiver(0)->getNumReflections());
    for(int i = 0; i < m_room.getReceiver(0)->getNumReflections(); i++)
    {
        m_delays[i] = new TappedDelay(m_room.getReceiver(0)->getReflections()[i][0], 0);;
        // std::cout << "Reflections: " << room.getReflections()[i][0]<< std::endl;
    }
}

void ReflectionManager::setBypass(bool bypassOn)
{
    m_bypassOn = bypassOn;
}

void ReflectionManager::setNormalised(bool normalised)
{
    m_normalised = normalised;
}