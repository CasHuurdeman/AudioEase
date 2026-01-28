//
// Created by cashu on 12/03/2025.
//

#pragma once

class dspMath{
public:

  static float samplesToMs(int samples, int samplerate){
    return static_cast<float>(samples)*1000.0f / static_cast<float>(samplerate);
  }

  static float msToSamples(float ms, unsigned int samplerate){
    return ms * static_cast<float>(samplerate) / 1000.0f;
  }
};