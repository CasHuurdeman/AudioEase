//
// Created by cashu on 11/11/2025.
//

#pragma once
#include <vector>
#include <array>

//This room is three-dimensional and rectangular, for more dimensions the code should be updated
class Room {
public:
    Room();
    ~Room();

    void calculateReflections();
    void calculateMirrorSources();
    //createRoom(float x, float y, float z), doe met alle functies?
    void createRoom();
    //TODO - is this the way to go -> yes, maybe even remove createRoom()
    void createWalls();

    //numMirrorSources is the same as numReflections
    int getNumReflections() const { return m_numMirrorSources; }
    float getSourceAmplitude() const { return m_sourceAmplitude; }
    std::vector<std::array<float, 2>>& getReflections() { return m_reflections;}


    float calculateDistance(float coordinatesA[], float coordinatesB[], int sizeA, int sizeB);
    float square(float value) { return value*value; }

private:
  //Array with coordinates of the corners
  std::array< std::array<float,2> ,4> m_roomCorners;
  std::array< float, 3> m_roomDimensions = {200.0f, 200.0f, 0.0f};

  //TODO - Only 1 receiver and 1 source now
  //these are the coordinates (in meters) of the source and receiver
  float m_receiver[3] = {2.0f, 0.0f, 0.0f};
  float m_source[3] = {10.0f, 40.0f, 0.0f};
  std::vector< std::array<float, 2> > m_mirrorSources;

  //TODO - do I want this here or do I want it as a return of calculateReflections
    //0 --> delayTimes, 1--> amplitudes
  std::vector< std::array< float, 2> > m_reflections;

  float m_sourceAmplitude = 0.0f;
  int m_numMirrorSources = 0;
  int m_maxOrder = 1;
  //Do we need this?
  int m_numDimensions = 2;

  enum coordinateIndex { topL = 0, topR, bottomR, bottomL, X = 0, Y = 1 };
};

