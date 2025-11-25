//
// Created by cashu on 25/11/2025.
//

#pragma once
#include <iostream>

//TODO - how does this work
class CustomPrint
{
public:

  template<typename T>
  void print(T t)
  {
    std::cout << t << std::endl;
  }

  //PRINT ONCE FUNCTION
  template<typename T, typename... Args>
  void printOnce(T t, Args... args)
  {
    if (!printed)
    {
      std::cout << t;
      print(args...);
      printed = true;
    }
  }

  //PRINT PERIODICALLY FUNCTION
  template<typename T, typename... Args>
  void printPeriodically(int period, T t, Args... args)
  {
    if (k == period)
    {
      std::cout << t;
      print(args...);
      k = 0;
    }
    k++;
  }


private:
  bool printed = false;
  int k = 0;
};