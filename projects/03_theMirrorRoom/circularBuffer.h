//
// Created by cashu on 04/11/2025.
//

#pragma once
#include <juce_audio_basics/buffers/juce_AudioSampleBuffer.h>

class CircularBuffer
{
public:
  CircularBuffer() = default;
  CircularBuffer(float samplesDelay);
  CircularBuffer(float samplesDelay, int bufferSize);
  ~CircularBuffer();

  //TODO - why cant I use auto
  //Writes to m_buffer
  void write(juce::AudioBuffer<float> inputBuffer);
  //writes to outputBuffer
  float read();
  //TODO - Is this needed?, maybe not for this particular one
//  float readWithoutIncrement();
  void wrap(int& head);
  void initReadHead();

  //getters and setters
  int getBufferSize() { return m_bufferSize; }
  int getSamplesDelay() { return m_samplesDelay; }

  //Make a setBufferSize only if needed
  void setSamplesDelay(float samplesDelay);

private:
  float* m_buffer = nullptr;
  int m_bufferSize = 0;
  float m_samplesDelay= 0.0f;

  float m_sampleOffset = 0.0f;
  int m_readHead = 0;
  int m_writeHead = 0;
};

