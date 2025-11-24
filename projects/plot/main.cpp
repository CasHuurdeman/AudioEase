//
// Created by cashu on 12/11/2025.
//
// including code from https://www.youtube.com/watch?v=mYBr-Yb70Z4
//
// #include "../03_theMirrorRoom/reflectionManager.h"
#include "pulse.h"
#include "writeToFile.h"
#include <iostream>
#include <cmath>
#include "../04_tappedDelay/delay.h"

int main()
{
    std::string sourceDir = SOURCE_DIR;
    WriteToFile fileWriter{sourceDir};


     // ReflectionManager reflectionManager;
     Delay delay{1000.0f};
        delay.addDelayLine(300.0f);
     Pulse pulse;

     for (int i = 0; i < 4800; i++)
     {
         fileWriter.writeToFile(delay.process(pulse.givePulse()));
     }

     return 0;
}
