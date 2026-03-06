//
// Created by cashu on 12/11/2025.
//
// including code from https://www.youtube.com/watch?v=mYBr-Yb70Z4
//
// #include "../03_theMirrorRoom/reflectionManager.h"
#include <algorithm>

#include "testSignal.h"
#include "writeToWAV.h"
#include "readWAV.h"
#include "writeToFile.h"
#include <iostream>
#include "files/reflectionManager.h"

int sampleRate = 48000;

int main()
{
    std::string sourceDir = SOURCE_DIR;

    TestSignal pulse;
    TestSignal pulse2;
    ReflectionManager reflectionManager;

    WriteToFile fileWriter{sourceDir};
    WriteToWAV wavWriter{"impulse_response2D", sourceDir, sampleRate};


    reflectionManager.prepare(sampleRate, 2);
    reflectionManager.changeNumReflections(30);
    reflectionManager.turnOnZaxis(false);

    int size = sampleRate * 2.5f;
     for (int i = 0; i < size; i++)
     {
         int numSamplesLeft = sampleRate - i;
         float signalL = reflectionManager.process(pulse.givePulse(), 0, numSamplesLeft);
         float signalR = reflectionManager.process(pulse2.givePulse(), 1, numSamplesLeft);


         if (i == size/10) std::cout << "10%..." << std::endl;
         if (i == size/2)
         {
             std::cout << "halfway there" << std::endl;
         }

         fileWriter.writeToFile(signalL);
         wavWriter.write(signalL,signalR);
     }

     return 0;
}
