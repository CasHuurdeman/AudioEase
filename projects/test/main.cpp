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
#include <speedTest.h>

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


std::vector<int> v2;
void printCopy(vector<int>& v) {
    v2 = v;
    std::cout << v2[3] << std::endl;
}

    // vector<int> v = {0,1,2,3,4};
vector<std::array<float, 2>> v = {{0,0}, {-40,100}, {5.1,6}, {5,6.1}};

int main() {
    vector<std::array<float, 2>>::iterator maxElement = std::max_element(
        v.begin(),
        v.end());

    std::cout << maxElement[-1][0] << maxElement[0][1] << std::endl;

    // SpeedTest s;
    //
    // s.start();
    // for (int i = 0; i < 100000; i++) {
    //
    // v.clear();
    // v.resize(5,1);
    // }
    // s.printSpeed();
    //
    // s.start();
    // for (int i = 0; i < 100000; i++) {
    //
    //     fill(v.begin(), v.end(), 1);
    // }
    // s.printSpeed();
    //
    // for (int i : v){ std::cout << i << std::endl;}

    // int m_fftSize = 511;
    //
    // int a = 1;
    // while (a < m_fftSize)
    // {
    //     a <<= 1;
    // }
    // std::cout << a << std::endl;

    // std::vector<int> v1 = {1,2,3,4};
    //
    // printCopy(v1);


    // std::vector<int> v1;
    // std::vector<int> v2;
    // SpeedTest s1;
    //
    // s1.start();
    // for (int i = 0; i < 1000000; i++)
    // {
    //     v1.push_back(4);
    // }
    // for (int i = 0; i < 1000000; i++)
    // {
    //     v2.push_back(5);
    // }
    // s1.printSpeed();
    //
    // s1.start();
    // for (int i = 0; i < 1000000; i++)
    // {
    //     v1.push_back(4);
    //     v2.push_back(5);
    // }
    // s1.printSpeed();

    // ReadWAV read("test.wav", sourceDir);
    //
    // read.readWavFile();
    //
    // read.getMetaData();

    // for (int i = 0; i < 1000; i++) {
    // std::cout << read.getSamplesL()[i] << std::endl;
    // }

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
