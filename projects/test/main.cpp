//
// Created by cashu on 12/11/2025.
//
// including code from https://www.youtube.com/watch?v=mYBr-Yb70Z4
//
#include "../03_theMirrorRoom/reflectionManager.h"
#include "pulse.h"
#include "writeToFile.h"
#include <iostream>

int main()
{
    WriteToFile fileWriter(SOURCE_DIR);


    ReflectionManager reflectionManager;
    Pulse pulse;

    for (int i = 0; i < 4800; i++)
    {
        fileWriter.writeToFile(reflectionManager.process(pulse.givePulse()));
    }

    return 0;
}
