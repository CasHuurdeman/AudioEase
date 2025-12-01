//
// Created by cashu on 11/11/2025.
//

#pragma once
#include <vector>
#include <array>
#include "receiver.h"

using std::vector;
using std::array;
using std::size;

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
    void prepareReceivers(int numChannels);

    //=======================ADD/REMOVE RECEIVER===============================
    void addReceiver(float X, float Y, float Z) { m_receiverVector.push_back(new Receiver(X, Y, Z)); }
    void removeReceiver(int receiverIndex); //TODO - IS THIS NEEDED?


    //=============================GETTERS=====================================
    [[nodiscard]] int getNumMirrorSources() const { return size(m_mirrorSources); }
    [[nodiscard]] float getMaxDelay() const { return m_maxDelay; }
    Receiver*& getReceiver(const int index) { return m_receiverVector[index]; } //TODO - & ????
    //=========================================================================


private:
    //EVERYTHING IS IN METERS
  float m_roomDimensions [3] = {6.0f, 6.0f, 6.0f};

  float m_source[3] = {2.5f, 1.2f, 1.7f};
  vector< array<float, 3> > m_mirrorSources;

  vector<Receiver*> m_receiverVector;

  float m_maxDelay = 0.0f;
  float m_soundSpeed = 343.0f;  //in m/s @20 deg celcius

  enum m_coordinateIndex { X = 0, Y = 1, Z = 2 };
};

