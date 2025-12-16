//
// Created by cashu on 13/03/2025.
//

#pragma once
#include <iostream>

class Pulse
{
public:
    Pulse() { count = 0; }
    ~Pulse() = default;

    int getCount() { return count; }

    float givePulse()
    {
        if(count == 0)
        {
            count++;
            return 1.0f;
        }
        else
        {
            count++;
            return 0.0f;
        }
    }

    float giveDC()
    {
        return 1.0f;
    }

    //starting with -1
    float giveNyquist()
    {
        count++;
        return pow(-1, count);
    }

    float sine(float freq, int sampleRate)
    {
        float signal = 0.5 * sin(PI*2 * 440.0f * count/48000);
        count++;
        // if (count >= sampleRate) count = 0;
        return signal;
    }


private:
    int count;
    float PI = 4* atan(1);
};