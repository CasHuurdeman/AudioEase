//
// Created by cashu on 25/11/2025.
//

#pragma once
#include <cmath>

class CalculateDistance
{
public:
    static float square(float value) { return value*value; }

    static float calculateDistance(float coordinatesA[], float coordinatesB[], size_t sizeA, size_t sizeB) {
        //manage array sizes
        int arraySize;
        if (sizeA < sizeB) arraySize = sizeA;
        else arraySize = sizeB;

        float value = 0;
        for (int i = 0; i < arraySize; i++)
        {
            value += square(coordinatesA[i] - coordinatesB[i]);
        }

        return sqrt(value);
    }
};
