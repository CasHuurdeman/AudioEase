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
  float process(float input, int channel);
  // void updateDelays??

  void createDelays();

  //=========================GETTERS AND SETTERS======================================
  [[nodiscard]] bool getBypassStatus() const { return m_bypassOn; }
  void setBypass(const bool bypassOn) { m_bypassOn = bypassOn; }

private:
  Room m_room;
  vector<CircularBuffer*> m_buffers;

  float m_feedback = 0.0f;
  bool m_bypassOn = false;
  int m_numChannels = 0;
  int m_sampleRate = 48000;

  SpeedTest speedTest;
};

