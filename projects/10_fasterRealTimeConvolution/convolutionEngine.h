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
  void convolve();

  //little circular buffer inside of the function
  void writeToBufferAndFFT(vector<float>& input);
  vector<float>& read();
  void wrap(int& head);

private:
  int m_readHeadInput = 0;
  int m_writeHead = 0;
  vector<float> m_inputBuffer;
  int m_readHeadIR = 0;
  vector<float> m_impulseResponse;
  vector<float> m_overlappingBuffer;

  int m_dataBlockSize = 0;
  int m_fftSize = 0;
  int m_numIRs = 0;

  int m_IRSize = 0;
};

