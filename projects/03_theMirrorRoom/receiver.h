//
// Created by cashu on 19/11/2025.
//

#pragma once
#include <vector>
#include <array>

using std::vector;
using std::array;
using std::size;

class Receiver{

public:
    Receiver() = default;
    Receiver(float X, float Y, float Z);
    ~Receiver();

    //FIXME - I DONT NEED TO KNOW EVERY REFLECTION EVERY TIME I MOVE, JUST THE ONES THAT GET TO THE RECEIVER IN THAT SPECIFIC MOMENT
    void calculateReflections(vector< array<float, 2> > mirrorSources,
        int numMirrorSources, float soundSpeed);
    void calculateSourceAmplitude(float source[], size_t arrayLength);

    //================================GETTERS================================================
    float getSourceAmplitude() const { return m_sourceAmplitude; }
    vector< array<float, 2> >& getReflections() { return m_reflections;}
    int getNumReflections() const { return static_cast<int>(m_reflections.size()); }

private:
    float m_coordinates[3] {0.0f, 0.0f, 0.0f};
    vector< array< float, 2> > m_reflections;

    float m_sourceAmplitude = 0.0f;
};

