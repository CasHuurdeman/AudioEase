//
// Created by cashu on 04/11/2025.
//

#pragma once
#include <vector>
#include <array>

using std::vector;
using std::array;

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

  // [i][0] = delay, [i][1] = targetDelay
  vector< array<float, 2> >& getSamplesDelay() { return m_samplesDelay; }

  void setSamplesDelay(int readHeadIndex, float samplesDelay);
  void setTargetSamplesDelay(int readHeadIndex, float samplesDelay);

private:
  float* m_buffer = nullptr;
  int m_bufferSize = 0;

  // [i][0] = delay, [i][1] = targetDelay
  vector< array<float, 2> > m_samplesDelay;

  vector<float> m_readHeads = {};
  int m_writeHead = 0;
};

