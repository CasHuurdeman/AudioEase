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
    void calculateMaxDelay();

    void changeReceivers(float distance);
    void changeNumReflections(int diagonalOrder);

    //============================RECEIVER===============================
    void addReceiver(float X, float Y, float Z) { m_receivers.push_back(new Receiver(X, Y, Z)); }
    //verwarrende naam
    void calcReflectionsForAllReceivers();

    //=============================GETTERS=====================================
    [[nodiscard]] int getNumMirrorSources() const { return size(m_mirrorSources); }
    [[nodiscard]] float getMaxDelay() const { return m_maxDelay; }
    Receiver*& getReceiver(const int index) { return m_receivers[index]; }
    float* getSource(){ return m_source; } //WATCH OUT!! NO WAY OF KNOWING HOW LONG THE ARRAY IS
    int getDiagonalOrder(){ return m_diagonalOrder; }
    float getReceiverDistance(){ return m_receiverDistance; }
    bool getZaxisOn(){ return m_ZaxisOn; }
    //=========================================================================
    void setSource(float X, float Y, float Z);
    void setRoomDimensions(float X, float Y, float Z);
    void setZaxisOn(bool ZaxisOn) { m_ZaxisOn = ZaxisOn; }

private:
    //EVERYTHING IS IN METERS
  float m_roomDimensions [3] = {10.0f, 10.0f, 3.0f};  //TODO - roomsize
  int m_diagonalOrder = 0;

  float m_source[3] = {0.3262f, 0.586f, 0.5f};
  vector< array<float, 3> > m_mirrorSources;

  float m_receiverDistance = 0.17;
  vector<Receiver*> m_receivers;

  float m_maxDelay = 0.0f;
  float m_soundSpeed = 343.0f;  //in m/s @20 deg celcius

  bool m_ZaxisOn = false;

  enum m_coordinateIndex { X = 0, Y = 1, Z = 2 };
};

