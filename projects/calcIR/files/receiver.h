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

    void calculateReflections(vector< array<float, 3> > mirrorSources,
        int numMirrorSources, float soundSpeed);

    //================================GETTERS================================================
    // m_reflections[i][0] = target? delayTime in ms;
    // m_reflections[i][1] = target amplitude;
    vector< array<float, 2> >& getReflections() { return m_reflections; }

    //returns the amplitude
    vector<float>& getSourceAmplitude(){ return m_sourceAmplitudes; }
    void setSourceAmplitude(int i, float amp);
    int getNumReflections() const { return static_cast<int>( m_reflections.size()); }

    float getXCoordinate() { return m_coordinates[0]; }
    float getYCoordinate() { return m_coordinates[1]; }


    //UI

private:
    float m_coordinates[3] {0.0f, 0.0f, 0.0f};
    vector< array< float, 2> > m_reflections;
    vector<float> m_sourceAmplitudes;
};

