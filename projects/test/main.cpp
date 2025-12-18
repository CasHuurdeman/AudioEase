//
// Created by cashu on 12/11/2025.
//
// including code from https://www.youtube.com/watch?v=mYBr-Yb70Z4
//
#include <iostream>
#include <fstream>
#include <complex>
#include <array>
#include <vector>
#include <cmath>
#include "readWAV.h"
#include "writeToWAV.h"
#include "../04_tappedDelay/circularBuffer.h"
#include "binFile.h"
#include "interpolation.h"
#include "smoothe.h"

std::string sourceDir = SOURCE_DIR;

int squareLoop(int x) {
    if (x >= 16) return x;
    x = x*x;
    squareLoop(x);
    std::cout << "Hoi\n"; //dit is gek
}
float devide(float num, float den)
{
    return (num / den);
}


int main() {
    ReadWAV read("test.wav", sourceDir);

    read.readWavFile();

    for (int i = 0; i < 1000; i++) {
    std::cout << read.getSamplesL()[i] << std::endl;
    }

    // float smoothedValue = 4.393579;
    // for (int i = 0; i < 7; i++) {
    //     smoothedValue = Smoothe::smootheValue(smoothedValue, 34.35735893, 5-i);
    //     std::cout << smoothedValue << std::endl;
    // }


    // float value = 4;
    // interpolation.setTarget(value, 4, 5);
    //
    // for (int i = 0; i < 9; i++) {
    //     if (i == 3)     interpolation.setTarget(value, 5, 5);
    //     value = interpolation.smoothe(value);
    //
    //      std::cout << value << std::endl;
    // }


    // //Seeing which results I get by deviding by 0
    //     std::cout << devide(0,0) << std::endl;
    //     std::cout << devide(1,0) << std::endl;
    //     std::cout << devide (1, pow(10, -39)) << std::endl;
    //     std::cout << devide(1, pow(10, -38)) << std::endl;

    // // reading a wav file
    //     ReadWAV readWAV("test.wav", sourceDir);
    //     readWAV.readWavFile();
    //
    //     for (int i = 0; i < 1000; i++) {
    //
    //     std::cout << readWAV.getSamplesL()[i] << std::endl;
    //     }

    // //Sine write to wav
    //     float PI = 4* atan(1);
    //     WriteToWAV writeWAV("test", sourceDir, 48000);
    //
    //     for (int i = 0; i < 48000; i++){
    //         float freq = 440.0f;
    //         float signal = 1 * sin(2*PI * i/48000 * freq);
    //
    //         writeWAV.write(signal,signal);
    //     }

// //Writing and reading a binary file
//         std::ofstream outFile(sourceDir + "/data.bin", std::ios::binary);
//         float wdata = 990;
//         int16_t ndata = static_cast<int16_t>(wdata);
//         outFile.write(reinterpret_cast<char*>(&ndata), sizeof(int16_t));
//         outFile.close();
//
//         std::ifstream file(sourceDir + "/data.bin", std::ios::binary);
//         if (file) {
//             int16_t data;
//             while (file.read(reinterpret_cast<char*>(&data), sizeof(data))) {
//                 std::cout << data << std::endl;
//             }
//             file.close();
//         } else {
//             std::cerr << "Error opening file." << std::endl;
//         }

//     //CircBufferCheck
//   CircularBuffer circBuffer{10};
//   circBuffer.addReadHead(10);
//
//   for(int i = 0; i < 5; i++)
//   {
//     circBuffer.write(i);
//   }
// float output = 0;
//   for(int i = 0; i < 10; i++)
//   {
//     for (int j = 0; j < 2; j++) {
//        output += circBuffer.read(j);
//     }
//       std::cout << output << std::endl;
//   }

    return 0;
}
