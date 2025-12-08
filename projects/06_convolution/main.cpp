//
// Created by cashu on 01/12/2025.
//
#include <iostream>
#include <vector>
#include <array>
#include <complex>
#include "FFT.h"
using namespace std;

#define FFT true
typedef float T;

//TODO - maybe not needed
  // std::array<float, fftSize*2> X{};
  // X.fill(0);
  //
  // memcpy(&X, &signal, sizeof(signal));

int main()
{
  const int fftSize = 8;
  std::array<float, fftSize> X{1,1,1,1,0,0,0,0};
  std::array<float, fftSize> Y{0.5,0.5,0,0,0,0,0,0};
#if FFT


  std::array<float, fftSize> Z{0,0,0,0,0,0,0,0};


  realfft_packed(&X[0], fftSize);
  realfft_packed(&Y[0], fftSize);

  Z[0] = X[0] * Y[0];
  // std::cout << X[0] << ",0\n";
  for (int i = 2; i < fftSize; i+=2) {
    std::complex z1(X[i], X[i+1]);
    std::complex z2(Y[i], Y[i+1]);

    std::complex z = z1*z2;
    Z[i] = real(z);
    Z[i+1] = imag(z);

    std::cout << abs(z) << "," << arg(z) << "               " << real(z) << "," << imag(z) << "\n";
  }
  Z[1] = X[1]*Y[1];
  // std::cout << X[1] << ",0\n";

  irealfft_packed(&Z[0], fftSize);

  for (int i = 0; i < fftSize; i++) {
    std::cout << Z[i] << std::endl;
  }

#else
  //NORMAL CONVOLUTION
  std::cout << "\nNORMAL CONVOLUTION: \n";
  // constexpr float X[4] = {1,1,1,1};
  // constexpr float Y[4] = {0.5,0.5,0};
  vector<float> Z;

  for(int n = 0; n < 10; n++)
  {
    float sum = 0;
    for(int k = 0; k < 4; k++)
    {
      float a;
      if (n-k < 0 || fftSize <= n)  a = 0;
      else  a = X[n-k];

      float b;
      if (k < 0 || fftSize <= k) b = 0;
      else b = Y[k];

      sum += b * a;

    }
      std::cout << sum << std::endl;
      Z.push_back(sum);
  }

#endif

  return 0;
}
