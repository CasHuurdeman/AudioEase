//
// Created by cashu on 17/11/2025.
//
// Code from https://www.youtube.com/watch?v=rHqkeLxAsTc
//
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

const int fileDuration = 2;
//maxAmplitude (16 bit): 2^15 / 2 - 1 = 32767.
// devided by 2 because its amplitude (so pos/neg) and 1 to exclude 0, if not clear, see the video on top
const int maxAmplitude = 32767;
const float freq = 440;


//Riff Chunk
const std::string chunkID = "RIFF";
const std::string chunkSize = "----";
const std::string format = "WAVE";

//FMT sub-chunk
const std::string subchunk1ID = "fmt "; // DONT FORGET SPACE AFTER FMT --> needs to be 4 bit
const int subchunk1Size = 16;
const int audioFormat = 1; //PCM = 1 -> linear quantization, other values indicate some form of compression
const int numChannels = 2;
const int sampleRate = 48000;
const int byteRate = sampleRate * numChannels * (subchunk1Size/2);
const int blockAlign = numChannels * (subchunk1Size / 8);
const int bitsPerSample = 16;

//DATA subchunk
const std::string subchunk2ID = "data";
const std::string subchunk2Size = "----";

void writeAsBytes(std::ofstream &file, int value, int byteSize)
{
  file.write(reinterpret_cast<const char*>(&value), byteSize);
}


int main()
{

  std::ofstream wav;

  const std::string sourceDir = SOURCE_DIR;
  wav.open(sourceDir + "test.wav", std::ios::binary);

  if( wav.is_open())
  {
    wav << chunkID;
    wav << chunkSize;
    wav << format;

    wav << subchunk1ID;
    writeAsBytes(wav, subchunk1Size, 4);
    writeAsBytes(wav, audioFormat, 2);
    writeAsBytes(wav, numChannels, 2);
    writeAsBytes(wav, sampleRate, 4);
    writeAsBytes(wav, byteRate, 4);
    writeAsBytes(wav, blockAlign, 2);
    writeAsBytes(wav, bitsPerSample, 2);

    wav << subchunk2ID;
    wav << subchunk2Size;


    //tellp() returns in which bit of the file you are
    int startAudio = wav.tellp();

    for(int i = 0; i < sampleRate * fileDuration; i++)
    {
      float amplitude = i / sampleRate * maxAmplitude;
      float value = sin((8 * atan(1) * i * freq) / sampleRate);

      //immediate fade in left and fade out right
      float channel1 = amplitude * value;
      float channel2 = (maxAmplitude - amplitude) * value;

      writeAsBytes(wav, channel1, 2);
      writeAsBytes(wav, channel2, 2);
    }
    int endAudio = wav.tellp();

    //update the subchunk2Size
    wav.seekp(startAudio - 4); //change to wav.seekp(36, std::ios::beg)
    writeAsBytes(wav, endAudio - startAudio, 4);

    //update the chunkSize (4 bites afway from the beginning of the file)
    wav.seekp(4, std::ios::beg);
    writeAsBytes(wav, endAudio - 8, 4);// 36 + subchunk2Size)
  }

  wav.close();

  return 0;
}

//schrijf meteen 32bit float weg (ipv 16bit, pcm)