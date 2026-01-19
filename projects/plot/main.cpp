//
// Created by cashu on 12/11/2025.
//
// including code from https://www.youtube.com/watch?v=mYBr-Yb70Z4
//
// #include "../03_theMirrorRoom/reflectionManager.h"
#include <algorithm>

#include "testSignal.h"
#include "writeToFile.h"
#include "writeToWAV.h"
#include "readWAV.h"
#include <iostream>
#include <cmath>
#include "../03_theMirrorRoom/reflectionManager.h"
// #include "../05_delay/delay.h"
#include "speedTest.h"

int sampleRate = 48000;

int main()
{
    std::string sourceDir = SOURCE_DIR;

    TestSignal pulse;
    ReflectionManager reflectionManager;
    // Delay delay{static_cast<float>(sampleRate), 0};
    SpeedTest speed_test;

    WriteToFile fileWriter{sourceDir};
    WriteToWAV wavWriter{"test", sourceDir, sampleRate};



     reflectionManager.prepare(sampleRate, 1);

    // speed_test.start();
     for (int i = 0; i < sampleRate *1.5; i++)
     {
         int numSamplesLeft = sampleRate - i;
         // float signal = reflectionManager.process(pulse.givePulse(), 0, numSamplesLeft);
         // float signal = delay.process(pulse.givePulse());
         // float signal = pulse.giveDC();
         // fileWriter.writeToFile(signal);
         float signal = 0;
         if (i == 0) signal = 1;

         wavWriter.write(signal,signal);
     }
    // speed_test.printSpeed();

     return 0;
}
