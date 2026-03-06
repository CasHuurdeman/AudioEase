//
// Created by cashu on 13/11/2025.
//

#pragma once
#include <vector>
#include "room.h"
#include "circularBuffer.h"
#include "speedTest.h"

using std::vector;

class ReflectionManager {
public:
  ReflectionManager();
  ~ReflectionManager();

  void prepare(int sampleRate, int numChannels);
  float process(float input, int channel, int numSamplesLeft);

  void createDelays();
  void updateDelays();
  //needs to be called when anything inside of the room changes
  void reloadRoom();

  //=========================GETTERS AND SETTERS======================================
  [[nodiscard]] bool getBypassStatus() const { return m_bypassOn; }
  void setBypass(const bool bypassOn) { m_bypassOn = bypassOn; }
  void setNormalise(const bool normaliseOn) { m_normalise = normaliseOn; }

  Room& getRoom() {return m_room; }

  //UI
  void turnOffDirectSound(float dimFactor);
  void turnOnDirectSound();

  void moveSource(float X, float Y, float Z);
  void moveReceivers(float distance)
  {
    m_room.changeReceivers(distance);
    updateDelays();
  }
  void changeNumReflections(int diagonalOrder)
  {
    m_room.changeNumReflections(diagonalOrder);
    createDelays();
  }
  void changeRoomDimensions(float X, float Y, float Z);
  void turnOnZaxis( bool ZaxisOn);

private:
  Room m_room{1};
  vector<CircularBuffer*> m_buffers;

  float m_feedback = 0.0f;
  bool m_bypassOn = false;
  bool m_normalise = false;
  int m_numChannels = 0;
  int m_sampleRate = 48000;

  vector<float> m_directSound;
  bool m_directSoundOn = true;
};

