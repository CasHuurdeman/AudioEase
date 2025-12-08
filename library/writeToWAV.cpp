//
// Created by cashu on 18/11/2025.
//
#include "writeToWAV.h"

WriteToWAV::WriteToWAV(const std::string& name, const std::string& sourcePath, const int sampleRate, int numChannels)
{
    m_numChannels = numChannels;
    m_sampleRate = sampleRate;
    m_wav.open(sourcePath + "/" + name + ".wav", std::ios::binary);

    //PUT ALL METADATA IN THE WAV FILE
    m_wav << m_chunkID;
    m_wav << m_chunkSize;
    m_wav << m_format;

    m_wav << m_subchunk1ID;
    writeAsBytes(m_wav, m_subchunk1Size, 4);
    writeAsBytes(m_wav, m_audioFormat, 2);
    writeAsBytes(m_wav, m_numChannels, 2);
    writeAsBytes(m_wav, m_sampleRate, 4);
    writeAsBytes(m_wav, m_byteRate, 4);
    writeAsBytes(m_wav, m_blockAlign, 2);
    writeAsBytes(m_wav, m_bitsPerSample, 2);

    m_wav << m_subchunk2ID;
    m_wav << m_subchunk2Size;


    //tellp() returns in which bit of the file you are
    startAudio = m_wav.tellp();
}

WriteToWAV::~WriteToWAV()
{
    endAudio = m_wav.tellp();

    //update the subchunk2Size
    //value = subchunk2Size
    int subchunk2Size = static_cast<int>(endAudio - startAudio);
    m_wav.seekp(40, std::ios::beg);
    writeAsBytes(m_wav, subchunk2Size, 4);

    //update the chunkSize (4 bites away from the beginning of the file)
    m_wav.seekp(4, std::ios::beg);
    writeAsBytes(m_wav, 36 + subchunk2Size, 4);

    //update numChannels
    m_wav.seekp(22, std::ios::beg);
    writeAsBytes(m_wav, m_numChannels, 2);

    m_wav.close();
}


void WriteToWAV::writeAsBytes(std::ofstream &file, auto value, const int byteSize)
{
    file.write(reinterpret_cast<const char*>(&value), byteSize);
}

//change to make it for n channels?
void WriteToWAV::write(const float channel1, const float channel2)
{
    writeAsBytes(m_wav, channel1*32767.0f, 2);
    writeAsBytes(m_wav, channel2*32767.0f, 2);
}

void WriteToWAV::writeToWAVMono(float channel)
{
    writeAsBytes(m_wav, channel, 2);
}
