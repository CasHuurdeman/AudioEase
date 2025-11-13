//
// Created by cashu on 12/03/2025.
//

#pragma once

class dspMath{
public:

  static float samplesToMs(int samples, int samplerate){
    return ((samples*1000.0f)/samplerate);
  };

  static float msToSamples(float ms, unsigned int samplerate){
    return (ms*samplerate)/1000.0f;
  };
};