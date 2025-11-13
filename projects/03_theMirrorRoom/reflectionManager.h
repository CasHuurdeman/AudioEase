//
// Created by cashu on 13/11/2025.
//

#pragma once
#include <vector>
#include "grid.h"
#include "delay.h"

class ReflectionManager {
public:
  ReflectionManager();
  ~ReflectionManager();

  void createDelays();
  float process(float input);

  float getBypassStatus() const { return m_bypassOn; }
  void setBypass(bool bypassOn);

private:
  Grid grid;
  std::vector<Delay*> m_delays;

  bool m_bypassOn = false;
};

