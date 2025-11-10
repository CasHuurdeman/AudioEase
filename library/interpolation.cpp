//
// Created by cashu on 11/02/2025.
//
#include "interpolation.h"
#include <iostream>


float Interpolation::nnMap(float value, float low, float high){
    //check if value is withing valid range
    if(value < 0){
        std::cout << "Interpolation::nnMap; Error: That's not between 0 and 1";
        return low;
    }
    if(value > 1){
        std::cout << "Interpolation::nnMap; Error: That's not between 0 and 1";
        return high;
    }
    //at this point the value is within range
    if(value < 0.5) return low;
    return high;
}

//using value1 and value2 instead of high and low, because high and low will now be checked inside the function
float Interpolation::linMap(float offset, float value1, float value2){

    //check if value is withing valid range
    if(offset < 0 || offset > 1){
        std::cout << "Interpolation::linMap; Error: offset out of range [0,1]\n"
        << " Offset: " << offset << std::endl;
        return value1;
    }

    return (value1 * (1.0f - offset))+(value2 * offset);
}

float Interpolation::mapInRange(float value, float fromLow, float fromHigh,
                     float toLow, float toHigh){

    float ratio = (value - fromLow)/(fromHigh - fromLow);

    return (toLow * (1.0 - ratio))+(toHigh * ratio);
}



//3*(1-0.3) + 2* 0.3 = 2.7