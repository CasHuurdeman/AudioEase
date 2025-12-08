//
// Created by cashu on 01/12/2025.
//
#include <iostream>
#include <array>
#include <complex>
#include "FFT.h"


int main()
{
  const int fftSize = 8;
  std::array<float, fftSize> X{1,1,1,1,0,0,0,0};
  std::array<float, fftSize> Y{0.5,0.5,0,0,0,0,0,0};

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

  for (int i : Z) {
    std::cout << i << std::endl;
  }

  return 0;
}
