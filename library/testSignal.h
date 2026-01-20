//
// Created by cashu on 13/03/2025.
//

#pragma once
#include <iostream>

class TestSignal
{
public:
    TestSignal()
    {
        std::cout << "TestSignal; WARNING - only one signal per object" << std::endl;
        count = 0;
    }
    ~TestSignal() = default;

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
        float signal = 0.2 * sin(PI*2 * freq * count/sampleRate);
        count++;
//         if (count >= sampleRate) count = 0;
        return signal;
    }

    float triangle(float freq, int sampleRate) {
        float signal = 4.0f*fabs((freq * count/sampleRate) - 0.5f) -1.0f;
        count++;
//        if (count >= sampleRate) count = 0;
        return signal;
    }



private:
    int count;
    float PI = 4* atan(1);
};