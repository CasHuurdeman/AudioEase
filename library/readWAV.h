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


//FIXME
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

    void read_wav_file()
    {
        if(m_wav.is_open())
        {
            // Read wave data
            sampleBuffer.resize( wav.sub_chunk2_size / sizeof(int16_t) );
            m_wav.read(reinterpret_cast<char*>( sampleBuffer.data() ), wav.sub_chunk2_size );

            // // Display some audio samples
            // const size_t numofsample = 840;
            // std::cout <<"Listin first " << numofsample << " Samples:" << std::endl;
            // for (size_t i = 0; i < numofsample && i < sampleBuffer.size(); ++i)
            // {
            //     std::cout << i << ":" << static_cast<float>(sampleBuffer[i])/32767 << std::endl;
            // }
            //
            // std::cout << std::endl;
        }
    }

    vector<int16_t>& getSampleBuffer(){ return sampleBuffer; }

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

private:
    std::ifstream m_wav;
    Twavheader wav{};

    vector<int16_t> sampleBuffer;
};

