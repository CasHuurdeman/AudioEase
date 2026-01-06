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
    explicit Room(int diagonalOrder);
    ~Room();

    void calculateMirrorSources();
    void calculateMaxDistance();

    //TODO - is this the way to go -> yes, maybe even remove createRoom()
    void createWalls();

    //============================RECEIVER===============================
    void addReceiver(float X, float Y, float Z) { m_receiverVector.push_back(new Receiver(X, Y, Z)); }
    void prepareReceivers(int numChannels);
    void updateReceivers();

    //=============================GETTERS=====================================
    [[nodiscard]] int getNumMirrorSources() const { return size(m_mirrorSources); }
    [[nodiscard]] float getMaxDelay() const { return m_maxDelay; }
    Receiver*& getReceiver(const int index) { return m_receiverVector[index]; }
    // float* getSource(){ return m_source; } //WATCH OUT!! NO WAY OF KNOWING HOW LONG THE ARRAY IS
    //=========================================================================
    void setSource(float X, float Y, float Z);

private:
    //EVERYTHING IS IN METERS
  float m_roomDimensions [3] = {20.0f, 20.0f, 3.0f};
  int m_diagonalOrder = 0;

  float m_source[3] = {1.5f, 1.0f, 1.7f};
  vector< array<float, 3> > m_mirrorSources;

  vector<Receiver*> m_receiverVector;

  float m_maxDelay = 0.0f;
  float m_soundSpeed = 343.0f;  //in m/s @20 deg celcius

  enum m_coordinateIndex { X = 0, Y = 1, Z = 2 };
};

