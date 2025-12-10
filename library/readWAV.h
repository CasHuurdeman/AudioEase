//
// Created by cashu on 02/12/2025.
//

#pragma once
#include <iostream>
#include <fstream>
#include <vector>

using std::vector;

// WAVE file header structure
struct Twavheader
{
    char chunk_ID[4];              //  4  riff_mark[4];
    uint32_t chunk_size;           //  4  file_size;
    char format[4];                //  4  wave_str[4];

    char sub_chunk1_ID[4];         //  4  fmt_str[4];
    uint32_t sub_chunk1_size;      //  4  pcm_bit_num;
    uint16_t audio_format;         //  2  pcm_encode;
    uint16_t num_channels;         //  2  sound_channel;
    uint32_t sample_rate;          //  4  pcm_sample_freq;
    uint32_t byte_rate;            //  4  byte_freq;
    uint16_t block_align;          //  2  block_align;
    uint16_t bits_per_sample;      //  2  sample_bits;

    char sub_chunk2_ID[4];         //  4  data_str[4];
    uint32_t sub_chunk2_size;      //  4  sound_size;
};                                 // 44  bytes TOTAL


class ReadWAV {
public:
    ReadWAV(const std::string& name, const std::string& sourcePath)
    {
        // Open the WAV file
        m_wav.open(sourcePath + "/" + name, std::ios::binary);

        // Read the WAV header
        m_wav.read(reinterpret_cast<char*>(&wav), sizeof(Twavheader));
    }

    ~ReadWAV()
    {
        m_wav.close();  // Close audio file
    }

    void readWavFile()
    {
        if(m_wav.is_open())
        {
            // Read wave data
            audioData.resize( wav.sub_chunk2_size / sizeof(int16_t) );
            m_wav.read(reinterpret_cast<char*>( audioData.data() ), wav.sub_chunk2_size );

            for (int i = 0; i < audioData.size(); i++) {
                float sample = static_cast<float>(audioData[i]) / 32767.0f;

                if (i%2 == 0) samplesL.push_back(sample);
                else samplesR.push_back(sample);
            }

            // for (int16_t sample: audioData) {
            //     sampleBuffer.push_back(static_cast<float>(sample) / 32767.0f);
            // }
        }
    }

    vector<float>& getSamplesL(){ return samplesL; }

    vector<float>& getSamplesR(){ return samplesR; }

    void getMetaData()
    {

        // Properties of WAV File
        std::cout << "File size:" << wav.chunk_size+8 << std::endl;
        std::cout << "Resource Exchange File Mark:" << std::string(wav.chunk_ID, 4) << std::endl;
        std::cout << "Format:" << std::string(wav.format, 4) << std::endl;
        std::cout << "Channels: " << wav.num_channels << std::endl;
        std::cout << "Sample Rate: " << wav.sample_rate << " Hz" << std::endl;
        std::cout << "Bits Per Sample: " << wav.bits_per_sample << " bits" << std::endl;
    }

    int getNumSamples()
    {
        if (wav.sub_chunk2_size < 1) return 0;
        return wav.sub_chunk2_size/(wav.bits_per_sample/8);
    }

private:
    std::ifstream m_wav;
    Twavheader wav{};

    vector<int16_t> audioData;
    vector<float> samplesL;
    vector<float> samplesR;
};

