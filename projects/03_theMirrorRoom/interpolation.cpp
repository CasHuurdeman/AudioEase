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

    //check which value is low and which is high
    float low,high;
    if (value1 < value2) {
       low = value1;
       high = value2;
    }
    else {low = value2; high = value1;}

    //check if value is withing valid range
    if(offset < 0){
        std::cout << "Interpolation::linMap; Error: That's not between 0 and 1 (<0)";
        return low;
    }
    if(offset > 1){
        std::cout << "Interpolation::linMap; Error: That's not between 0 and 1 (>1)";
        return high;
    }

    //at this point the value is within range
    return (low * (1.0 - offset))+(high * offset);
}

float Interpolation::mapInRange(float value, float fromLow, float fromHigh,
                     float toLow, float toHigh){

    float ratio = (value - fromLow)/(fromHigh - fromLow);

    return (toLow * (1.0 - ratio))+(toHigh * ratio);
}



//3*(1-0.3) + 2* 0.3 = 2.7