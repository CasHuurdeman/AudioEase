//
// Created by cashu on 12/11/2025.
//
// including code from https://www.youtube.com/watch?v=mYBr-Yb70Z4
//
// #include "../03_theMirrorRoom/reflectionManager.h"
#include <algorithm>

#include "pulse.h"
#include "writeToFile.h"
#include "writeToWAV.h"
#include "readWAV.h"
#include <iostream>
#include <cmath>
#include "../03_theMirrorRoom/reflectionManager.h"
#include "speedTest.h"

int sampleRate = 48000;

int main()
{
    std::string sourceDir = SOURCE_DIR;

    Pulse pulse;
    ReflectionManager reflectionManager;
    SpeedTest speed_test;

    WriteToFile fileWriter{sourceDir};
    WriteToWAV wavWriter{"test", sourceDir, sampleRate};



     reflectionManager.prepare(sampleRate, 1);

    speed_test.start();
     for (int i = 0; i < sampleRate/2; i++)
     {
         float signal = reflectionManager.process(pulse.givePulse(), 0);
         // float signal = pulse.giveNyquist();
         fileWriter.writeToFile(signal);
         wavWriter.write(signal,signal);
     }
    speed_test.printSpeed();

     return 0;
}
