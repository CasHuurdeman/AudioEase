//
// Created by cashu on 19/11/2025.
//

#include "receiver.h"
#include <iostream>
#include "calculateDistance.h"

Receiver::Receiver(float X, float Y, float Z)
{
  // std::cout << "Receiver - constructor" << std::endl;
    m_coordinates[0] = X;
    m_coordinates[1] = Y;
    m_coordinates[2] = Z;
}

Receiver::~Receiver()
{
    // std::cout << "Receiver - destructor" << std::endl;
}


void Receiver::calculateReflections(vector< array<float, 3> > mirrorSources, int numMirrorSources, const float soundSpeed)
{
    //does this take a lot of time?
    m_reflections.resize(numMirrorSources);
    m_sourceAmplitudes.resize(numMirrorSources);
    for (int i = 0; i < numMirrorSources; i++)
    {
        //Calculate distance from receiver to mirrorSources
        float distance = CalculateDistance::calculateDistance(mirrorSources[i].data(),
            m_coordinates, size(mirrorSources[i]), size(m_coordinates));

        //Make sure not to devide by 0 or a too small number (will get inf or NaN)
        if (distance < 0.5) distance = 0.5; //TODO - this works but how can I do this nicely

        //amplitude according to Richard Moore (Elements of computer music p370)
        float amplitude = 1.0f / distance;
        float delayTime = distance / soundSpeed * 1000.0f;

        m_sourceAmplitudes[i] = m_reflections[i][1];
        m_reflections[i][0] = delayTime;
        m_reflections[i][1] = amplitude;
    }
}

void Receiver::setSourceAmplitude(int i, float amp)
{
    if (amp > 2) std::cout << "Receiver::setMirrorSourcesAmplitude; ERROR - amplitude exceeds 2" << std::endl;
    else m_sourceAmplitudes[i] = amp;
}
