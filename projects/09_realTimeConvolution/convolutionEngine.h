//
// Created by cashu on 08/01/2026.
//

#pragma once

#include <vector>
using std::vector;

class ConvolutionEngine {
public:
  ConvolutionEngine();
  ~ConvolutionEngine();

  void prepare(int inputBufferSize, vector<float>& impulseResponse); //TODO - use reference or no?
  vector<float> process(vector<float>& input);

private:
  vector<float> m_inputBuffer;
  vector<float> m_impulseResponse;

  vector<float> m_overlappingBuffer;

  vector<float> m_outputBuffer;
  vector<float> m_tail;

  int m_fftSize = 0;
  int m_inputBufferSize = 0;
};

