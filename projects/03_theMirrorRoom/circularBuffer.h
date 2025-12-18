//
// Created by cashu on 04/11/2025.
//

#pragma once
#include <vector>

using std::vector;

//CircularBuffer with multiple readHeads
class CircularBuffer
{
public:
  CircularBuffer() = default;
  explicit CircularBuffer(int bufferSize);
  CircularBuffer(float samplesDelay, int bufferSize);
  ~CircularBuffer();

  void write(float input);
  float read(int readHeadIndex);
  void wrap(auto& head);
  void initReadHead(float& readHead, float samplesDelay);

  //TAPPED DELAY
  void addReadHead(float samplesDelay);
  void removeReadHead(int readHeadIndex);

  //getters and setters
  [[nodiscard]] int getBufferSize() const { return m_bufferSize; }
  [[nodiscard]] size_t getNumReadHeads() const { return m_readHeads.size(); }
  vector<float> getSamplesDelay() { return m_samplesDelay; }
  std::vector<float> getTargetSamplesDelay() { return m_targetSamplesDelay; }

  void setSamplesDelay(int readHeadIndex, float samplesDelay);
  void setTargetSamplesDelay(int readHeadIndex, float samplesDelay);

private:
  float* m_buffer = nullptr;
  int m_bufferSize = 0;

  vector<float> m_samplesDelay;
  vector<float> m_targetSamplesDelay;

  vector<float> m_readHeads = {};
  int m_writeHead = 0;
};

