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

     reflectionManager.prepare(1);

     for (int i = 0; i < 4800; i++)
     {
         fileWriter.writeToFile(reflectionManager.process(pulse.givePulse(), 0));
     }

     return 0;
}
