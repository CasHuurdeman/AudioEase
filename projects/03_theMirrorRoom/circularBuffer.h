//
// Created by cashu on 04/11/2025.
//

#pragma once
#include <vector>
#include <array>

class CircularBuffer
{
public:
  CircularBuffer() = default;
  CircularBuffer(int bufferSize);
  CircularBuffer(float samplesDelay, int bufferSize);
  ~CircularBuffer();

  void write(float input);
  float read(int readHeadIndex);
//  float readWithoutIncrement();
  void wrap(auto& head);
  void initReadHead(float& readHead, float samplesDelay);

  //TAPPED DELAY
  void addReadHead(float samplesDelay);
  //TODO - how will this work?
  void removeReadHead(int readHeadIndex);

  //getters and setters
  int getBufferSize() const { return m_bufferSize; }
  size_t getNumReadHeads() const { return m_readHeads.size(); }
  //special case of having the getter in the cpp file
  std::vector<float> getSamplesDelay();

  //TODO - do I even want a setSamplesDelay?
  void setSamplesDelay(int readHeadIndex, float samplesDelay);

private:
  float* m_buffer = nullptr;
  int m_bufferSize = 0;

  std::vector<float> m_readHeads= {};
  int m_writeHead = 0;
};

