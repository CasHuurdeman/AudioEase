//
// Created by cashu on 19/11/2025.
//

#include "receiver.h"
#include <iostream>

Receiver::Receiver(float X, float Y, float Z)
{
  std::cout << "Receiver - constructor" << std::endl;
    m_coordinates[0] = X;
    m_coordinates[1] = Y;
    m_coordinates[2] = Z;
}

Receiver::~Receiver()
{
    std::cout << "Receiver - destructor" << std::endl;
}


void Receiver::calculateReflections(float source[], size_t arrayLength, std::vector< std::array<float, 2> > mirrorSources, int numMirrorSources)
{
    float sourceDistance = calculateDistance(source, m_coordinates, arrayLength, std::size(m_coordinates));
    m_sourceAmplitude = 1 / pow(sourceDistance, 1.5f);
    // std::cout << "Distance: " << distance << "SourceAmplitude: " << getSourceAmplitude() << "\n" << std::endl;

    m_reflections.resize(numMirrorSources);
    for (int i = 0; i < numMirrorSources; i++)
    {
        //Calculate distance from receiver to mirrorSources
        float distance = calculateDistance(mirrorSources[i].data(), m_coordinates,
          std::size(mirrorSources[i]), std::size(m_coordinates));

        //amplitude according to Richard Moore (Elements of computer music p370)
        float amplitude = 1 / pow(distance, 1.5f);
        float delayTime = distance / m_soundSpeed * 1000;

        m_reflections[i][0] = delayTime;
        m_reflections[i][1] = amplitude;
        // std::cout << "DelayTime" << i << ": " << m_reflections[i][0] << "\nAmplitude" << i << ": " << m_reflections[i][1] << "\nDistance" << i << ": " << distance << "\n" << std::endl;
    }
}

float Receiver::calculateDistance(float coordinatesA[], float coordinatesB[], size_t sizeA, size_t sizeB) {
    //manage array sizes
    int arraySize;
    if (sizeA < sizeB) arraySize = sizeA;
    else arraySize = sizeB;

    float value = 0;
    for (int i = 0; i < arraySize; i++)
    {
        value += square(coordinatesA[i] - coordinatesB[i]);
    }

    return sqrt(value);
}