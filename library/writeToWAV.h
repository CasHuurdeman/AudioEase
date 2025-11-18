//
// Created by cashu on 17/11/2025.
//

#pragma once
#include <fstream>
#include <cmath>
#include <string>
//TODO - schrijf meteen 32bit float weg (ipv 16bit, pcm) OF EXTENDABLE

//writes to a stereo .wav file
class WriteToWAV {
public:
  WriteToWAV(const std::string& name, const std::string& sourcePath, int sampleRate);
  ~WriteToWAV();

  void writeAsBytes(std::ofstream &file, int value, int byteSize);
  void writeToWAV(float channel1, float channel2);

private:
  std::ofstream m_wav;
  long long startAudio = 0;
  long long endAudio = 0;

//WAV METADATA
  //Riff Chunk
  const std::string m_chunkID = "RIFF";
  const std::string m_chunkSize = "----";
  const std::string m_format = "WAVE";

  //FMT sub-chunk
  const std::string m_subchunk1ID = "fmt "; // DONT FORGET SPACE AFTER FMT --> needs to be 4 bit
  const int m_subchunk1Size = 16;
  const int m_audioFormat = 1; //PCM = 1 , 32bit float = 3
  int m_numChannels = 2;
  int m_sampleRate = 48000;
  const int m_byteRate = m_sampleRate * m_numChannels * (m_subchunk1Size/2);
  const int m_blockAlign = m_numChannels * (m_subchunk1Size / 8);
  const int m_bitsPerSample = 16;

  //DATA subchunk
  const std::string m_subchunk2ID = "data";
  const std::string m_subchunk2Size = "----";
};