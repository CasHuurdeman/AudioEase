//
// Created by cashu on 13/11/2025.
//

#include "reflectionManager.h"
#include <iostream>
#include "delay.h"
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


float ReflectionManager::process(float input)
{
    if(m_bypassOn){ return input; }

    float output = input;
    for(int i = 0; i < room.getNumReflections(); i++)
    {
        // /room.getSourceAmplitude -> To normalise the reflections for the input
        // (the same effect as input * room.getSourceAmplitude() and then gaining everything up)
      output += m_delays[i]->process(input) * room.getReflections()[i][1] / room.getSourceAmplitude();
    }
    return output;
}

void ReflectionManager::createDelays()
{
      m_delays.resize(room.getNumReflections());
      for(int i = 0; i < room.getNumReflections(); i++)
      {
        m_delays[i] = new Delay(room.getReflections()[i][0], 0);;
    // std::cout << "Reflections: " << room.getReflections()[i][0]<< std::endl;
      }
}

void ReflectionManager::setBypass(bool bypassOn)
{
    m_bypassOn = bypassOn;
}