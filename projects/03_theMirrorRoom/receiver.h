//
// Created by cashu on 19/11/2025.
//

#pragma once
#include <vector>
#include <array>

class Receiver{

public:
    Receiver() = default;
    Receiver(float X, float Y, float Z);
    ~Receiver();

    void calculateReflections(float source[], size_t arrayLength, std::vector< std::array<float, 2> > mirrorSources, int numMirrorSources);

    float getSourceAmplitude() const { return m_sourceAmplitude; }
    std::vector<std::array<float, 2>>& getReflections() { return m_reflections;}
    int getNumReflections() const { return m_reflections.size(); }

    float calculateDistance(float coordinatesA[], float coordinatesB[], size_t sizeA, size_t sizeB);
    float square(float value) { return value*value; }

private:
    float m_coordinates[3];
    float m_sourceAmplitude = 0.0f;

    float m_soundSpeed = 343.0f;  //in m/s @20 deg celcius

    //TODO - do I want this here or do I want it as a return of calculateReflections
    //0 --> delayTimes, 1--> amplitudes
    std::vector< std::array< float, 2> > m_reflections;
};

