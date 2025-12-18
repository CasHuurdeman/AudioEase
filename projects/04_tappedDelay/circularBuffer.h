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
  CircularBuffer(float samplesDelay);
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
  std::vector<float> getSamplesDelay() { return m_samplesDelay; }
  // std::vector<float> getReadSpeed() const { return m_readSpeed; }

  void setSamplesDelay(int readHeadIndex, float samplesDelay);
  // void setReadSpeed(int readHeadIndex, float readSpeed);

private:
  float* m_buffer = nullptr;
  int m_bufferSize = 0;
  std::vector<float> m_samplesDelay;

  // std::vector<float> m_readSpeed = {1.0f};
  std::vector<float> m_readHeads = {0.0f};
  int m_writeHead = 0;
};

