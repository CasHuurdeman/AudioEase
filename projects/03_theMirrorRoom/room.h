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

    //TODO - is this the way to go -> yes, maybe even remove createRoom()
    void createWalls();
    void calculateMirrorSources(int diagonalOrder);
    void calculateMaxDistance(int diagonalOrder);
    void prepare(int numChannels);

    //=======================ADD/REMOVE RECEIVER===============================
    void addReceiver(float X, float Y, float Z) { m_receiverVector.push_back(new Receiver(X, Y, Z)); }
    void removeReceiver(int receiverVectorIndex);


    //=============================GETTERS=====================================
    [[nodiscard]] int getNumMirrorSources() const { return m_numMirrorSources; }
    [[nodiscard]] float getMaxDelay() const { return m_maxDelay; }
    Receiver*& getReceiver(const int index) { return m_receiverVector[index]; } //TODO - & ????
    //=========================================================================


private:
  //these are the coordinates (in meters) of the source
  float m_source[3] = {2.3f, 1.2f, 0.0f};
  std::vector<Receiver*> m_receiverVector;

  float m_roomDimensions [3] = {6.0f, 6.0f, 0.0f};
  float m_maxDelay = 0.0f;

  //MIRROR SOURCES
  std::vector< std::array<float, 2> > m_mirrorSources;
  int m_numMirrorSources = 0;

  float m_soundSpeed = 343.0f;  //in m/s @20 deg celcius
  enum coordinateIndex { X = 0, Y = 1, Z = 2 };
};

