//
// Created by cashu on 04/11/2025.
//

#pragma once

class CircularBuffer
{
public:
  CircularBuffer() = default;
  CircularBuffer(float samplesDelay);
  CircularBuffer(float samplesDelay, int bufferSize);
  ~CircularBuffer();

  void write(float input);
  float read();
//  float readWithoutIncrement();
  void wrap(int& head);
  void initReadHead();

  //getters and setters
  int getBufferSize() const { return m_bufferSize; }
  float getSamplesDelay() const { return m_samplesDelay; }

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

