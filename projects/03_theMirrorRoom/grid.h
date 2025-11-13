//
// Created by cashu on 11/11/2025.
//

#pragma once
#include <vector>
#include <array>

//Lets for now hardcode everything
class Grid {
public:
    Grid();
    ~Grid();

    //TODO - now all void functions, change so there is less vectors and arrays to be used
    void calculateReflections();
    void calculateMirrorSources();
    void createRoom();
    //TODO - is this the way to go --> for later maybe
    void createWalls();

    std::vector<std::array<float, 2>>& getReflections() { return m_reflections;}
    //numMirrorSources is the same as numReflections
    int getNumReflections() { return m_numMirrorSources; }

    float square(float value) { return value*value; }

private:
  //TODO - do I want this here or do I want it as a return of calculateReflections
    //0 --> delayTimes 1--> amplitudes
  std::vector< std::array< float, 2> > m_reflections;

  //todo - make a scalable vector out of this?
  float m_roomHeight = 10.0f;
  float m_roomWidth = 10.0f;
  //Array with coordinates of the corners
  std::array<std::array<float,2>,4> m_roomCorners;

  //TODO - make a vector out of this and make it so that there can be multiple sources and receivers
  //these are the coordinates (in meters) of the source and receiver
  float m_source[2] = {3.0f, 3.0f};
  float m_receiver[2] = {0.0f, 0.0f};
  std::vector< std::array<float, 2> > m_mirrorSources;

  int m_numMirrorSoures = 0;
  //Do we need this?
  int m_maxOrder = 1;
  int m_numDimensions = 2;
};

