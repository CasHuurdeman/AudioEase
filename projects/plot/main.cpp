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
#include "../03_theMirrorRoom/reflectionManager.h"

int main()
{
    std::string sourceDir = SOURCE_DIR;
    WriteToFile fileWriter{sourceDir};


     ReflectionManager reflectionManager;
     Pulse pulse;

     reflectionManager.prepare(48000, 2);

     for (int i = 0; i < 48000; i++)
     {
         fileWriter.writeToFile(reflectionManager.process(pulse.givePulse(), 1));
     }

     return 0;
}
