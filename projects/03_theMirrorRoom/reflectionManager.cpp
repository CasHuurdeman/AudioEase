//
// Created by cashu on 13/11/2025.
//

#include "reflectionManager.h"
#include <iostream>
#include "delay.h"
//TODO - als ik er nu twee aanroep worden dezelfde dingen ook twee keer berekend. Dit is in pricipe niet erg straks als ik met twee oren/speakers ga werken, tenzij ik dat in de class zelf wil regelen
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
    for(int i = 0; i < grid.getNumReflections(); i++)
    {
        // /grid.getSourceAmplitude -> To normalise the reflections for the input
        // (the same effect as input * grid.getSourceAmplitude() and then gaining everything up)
      output += m_delays[i]->process(input) * grid.getReflections()[i][1] / grid.getSourceAmplitude();
    }
    return output;
}

void ReflectionManager::createDelays()
{
      m_delays.resize(grid.getNumReflections());
      for(int i = 0; i < grid.getNumReflections(); i++)
      {
        m_delays[i] = new Delay(grid.getReflections()[i][0], 0);;
      }
}

void ReflectionManager::setBypass(bool bypassOn)
{
    m_bypassOn = bypassOn;
}