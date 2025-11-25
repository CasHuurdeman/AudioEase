//
// Created by cashu on 11/11/2025.
//

#pragma once
#include <vector>
#include <array>
#include "receiver.h"

//This room is three-dimensional and rectangular, for more dimensions the code should be updated
class Room {
public:
    // Room() = default;
    Room();
    ~Room();

    void calculateMirrorSources(int diagonalOrder);
    //TODO - is this the way to go -> yes, maybe even remove createRoom()
    void createWalls();
    //createRoom(float x, float y, float z), doe met alle functies?
    // void createRoom();

    void prepare(int numChannels);

    //numMirrorSources is the same as numReflections
    int getNumMirrorSources() const { return m_numMirrorSources; }
    //TODO - & ????
    Receiver*& getReceiver(int index) { return m_receiverVector[index]; }
    float getMaxDelay() const { return m_maxDelay; }

    void addReceiver(float X, float Y, float Z);
    void removeReceiver(int receiverVectorIndex);
private:
  //these are the coordinates (in meters) of the source
  float m_source[3] = {6.0f, 5.0f, 0.0f};
  std::vector<Receiver*> m_receiverVector;
  std::array< float, 3> m_roomDimensions = {15.0f, 15.0f, 0.0f};

  std::vector< std::array<float, 2> > m_mirrorSources;
  int m_numMirrorSources = 0;

  float m_maxDelay = 0.0f;

  enum coordinateIndex { topL = 0, topR, bottomR, bottomL, X = 0, Y = 1, Z = 2 };
};

