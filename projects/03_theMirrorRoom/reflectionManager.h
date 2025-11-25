//
// Created by cashu on 13/11/2025.
//

#pragma once
#include <vector>
#include "room.h"
#include "tappedDelay.h"

class ReflectionManager {
public:
  ReflectionManager();
  ~ReflectionManager();

  void createDelays();
  float process(float input, int channel);

  float getBypassStatus() const { return m_bypassOn; }
  void setBypass(bool bypassOn);
  void setNormalised(bool normalised);

  void prepare(int numChannels);

private:
  Room m_room;
  std::vector<TappedDelay*> m_delays;

  bool m_bypassOn = false;
  int m_numChannels = 0;
  bool m_normalised = true;
};

