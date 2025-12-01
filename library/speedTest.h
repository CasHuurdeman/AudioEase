//
// Created by cashu on 01/12/2025.
//

#pragma once
#include <chrono>
#include <iostream>

using namespace std::chrono;

class SpeedTest
{
public:

  void start(){ startTest = high_resolution_clock::now(); }

  void printSpeed()
  {
    auto endTest = high_resolution_clock::now();

    double timeTaken = duration_cast<nanoseconds>(endTest - startTest).count();

    timeTaken *= 1e-9;

    std::cout << "Time taken by program is : " << std::fixed
         << timeTaken << std::setprecision(9);
    std::cout << " sec" << std::endl;
  }

private:
  time_point<steady_clock> startTest;

};
