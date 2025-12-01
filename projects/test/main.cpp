//
// Created by cashu on 12/11/2025.
//
// including code from https://www.youtube.com/watch?v=mYBr-Yb70Z4
//
#include <iostream>
#include <array>
#include <vector>
#include <cmath>
#include "../04_tappedDelay/circularBuffer.h"


int main()
{
    using namespace std;

    vector<array<int, 2>> A = {{1,2}, {3,4}, {5,6}};

    cout << size(A) << endl;

//   CircularBuffer circBuffer{10};
//   circBuffer.addReadHead(10);
//
//   for(int i = 0; i < 5; i++)
//   {
//     circBuffer.write(i);
//   }
// float output = 0;
//   for(int i = 0; i < 10; i++)
//   {
//     for (int j = 0; j < 2; j++) {
//        output += circBuffer.read(j);
//     }
//       std::cout << output << std::endl;
//   }

    return 0;
}
