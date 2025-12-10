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


private:
    int count;
};