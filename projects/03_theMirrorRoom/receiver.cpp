//
// Created by cashu on 19/11/2025.
//

#include "receiver.h"
#include <iostream>
#include "calculateDistance.h"

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


void Receiver::calculateReflections(vector< array<float, 3> > mirrorSources, const int numMirrorSources, const float soundSpeed)
{
    //does this take a lot of time?
    m_reflections.resize(numMirrorSources);
    for (int i = 0; i < numMirrorSources; i++)
    {
        //Calculate distance from receiver to mirrorSources
        float distance = CalculateDistance::calculateDistance(mirrorSources[i].data(),
            m_coordinates, size(mirrorSources[i]), size(m_coordinates));
        //Make sure not to devide by 0 or a too small number (will get inf or NaN)
        if (distance < 0.5) distance = 0.5; //TODO - this works but how can I do this nicely

        //amplitude according to Richard Moore (Elements of computer music p370)
        float amplitude = 1 / pow(distance, 1.5f);
        float delayTime = distance / soundSpeed * 1000;

        m_reflections[i][0] = delayTime;
        m_reflections[i][1] = amplitude;
        // std::cout << "DelayTime" << i << ": " << m_reflections[i][0] << "\nAmplitude" << i << ": " << m_reflections[i][1] << "\nDistance" << i << ": " << distance << "\n" << std::endl;
    }
}

void Receiver::calculateSourceAmplitude(float source[], size_t arrayLength) {
    float sourceDistance = CalculateDistance::calculateDistance(source, m_coordinates, arrayLength, std::size(m_coordinates));
    if (sourceDistance < 0.5) sourceDistance = 0.5; //TODO - this works but how can I do this nicely
    m_sourceAmplitude = 1 / pow(sourceDistance, 1.5f);
    // std::cout << "Distance: " << distance << "SourceAmplitude: " << getSourceAmplitude() << "\n" << std::endl;
}

void Receiver::setCoordinates(float X, float Y, float Z) {
    m_coordinates[0] = X;
    m_coordinates[1] = Y;
    m_coordinates[2] = Z;
    //calc reflections and source amplitude
}
