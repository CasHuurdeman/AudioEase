//
// Created by cashu on 13/11/2025.
//

#include "reflectionManager.h"
#include <iostream>
#include "delay.h"

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
return 0.0f;
}

void ReflectionManager::createDelays()
{
      for(int i = 0; i < grid.getNumReflections(); i++)
      {
          // std::cout << "ref: " << grid.getReflections()[i][0] << std::endl;
        Delay delay(grid.getReflections()[i][0], 0);
        m_delays.push_back(delay);
      }

}