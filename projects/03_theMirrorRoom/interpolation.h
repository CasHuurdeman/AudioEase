//
// Created by cashu on 11/02/2025.
//

#pragma once

class Interpolation {
  public:

    static float nnMap(float value, float low, float high);
    static float linMap(float offset, float value1, float value2);
    static float mapInRange(float value, float fromLow, float fromHigh,
                     float toLow, float toHigh);



};

