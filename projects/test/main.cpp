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
#include "../04_tappedDelay/circularBuffer.h"
#include "binFile.h"


    std::string sourceDir = SOURCE_DIR;


    int squareLoop(int x) {
        if (x >= 16) return x;
        x = x*x;
        squareLoop(x);
        std::cout << "Hoi\n"; //dit is gek
    }


int main()
{



        // BinFile binFile("test", sourceDir);
        // binFile.write(0.3f);
        // binFile.write(0.3f);
        // binFile.write(0.3f);
        //
        // binFile.read();
        // std::cout << binFile.getData()[0] << binFile.getData()[1] << binFile.getData()[2] << "\n";

       // std::cout << squareLoop(2) << "\n";

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
