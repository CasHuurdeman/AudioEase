//
// Created by cashu on 01/12/2025.
//
#include <iostream>
#include <vector>
#include <array>
#include <complex>
#include "FFT.h"
using std::vector;

//NORMAL CONVOLUTION = 0
//FFT CONVOLUTION = 1
//FFT DECONVOLUTION = 2
#define state 1

int main()
{
  const int fftSize = 8;
  std::vector<double> X{1,1,1,1,0,0,0,0};
  std::vector<double> Y{0.5,0.5,0,0,0,0,0,0};

#if state == 2
//====================FFT DECONVOLUTION=============================
  std::vector<double> Z{0,0,0,0,0,0,0,0};

  realfft_packed(&X[0], fftSize);
  realfft_packed(&Y[0], fftSize);

  for (int i = 0; i < fftSize; i++)
  {
    //TODO - can I do this if?
    if (i%2 ==0 || i == 1)
    {
      Y[i] += 0.00000001;
    }
  }

  Z[0] = X[0] / Y[0];
  // std::cout << X[0] << ",0\n";
  for (int i = 2; i < fftSize; i+=2) {
    std::complex z1(X[i], X[i+1]);
    std::complex z2(Y[i], Y[i+1]);

    std::complex z = z1/z2;
    Z[i] = real(z);
    Z[i+1] = imag(z);

    // std::cout << abs(z) << "," << arg(z) << "               " << real(z) << "," << imag(z) << "\n";
  }
  Z[1] = X[1]/Y[1];
  // std::cout << X[1] << ",0\n";

  irealfft_packed(&Z[0], fftSize);

  //Normalising (fftSize^2 because I normalise inside the fft for the convolution)
  for (int i = 0; i < fftSize; i++) {
    Z[i] /= fftSize;
  }

  for (int i = 0; i < fftSize; i++) {
    std::cout << Z[i] << std::endl;
  }

#elif state == 1
//============================FFT CONVOLUTION=======================================

  std::vector<double> Z{0,0,0,0,0,0,0,0};

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

    // std::cout << abs(z) << "," << arg(z) << "               " << real(z) << "," << imag(z) << "\n";
  }
  Z[1] = X[1]*Y[1];
  // std::cout << X[1] << ",0\n";

  irealfft_packed(&Z[0], fftSize);

  //Normalising
  for (int i = 0; i < fftSize; i++) {
    Z[i] *= fftSize;
  }

  for (int i = 0; i < fftSize; i++) {
    std::cout << Z[i] << std::endl;
  }



#else state == 0
//=========================NORMAL CONVOLUTION===================================

  // constexpr double X[4] = {1,1,1,1};
  // constexpr double Y[4] = {0.5,0.5,0};
  vector<double> Z;

  for(int n = 0; n < 10; n++)
  {
    double sum = 0;
    for(int k = 0; k < 10; k++)
    {
      double a;
      if (n-k < 0 || fftSize <= n)  a = 0;
      else  a = X[n-k];

      double b;
      if (k < 0 || fftSize <= k) b = 0;
      else b = Y[k];

      sum += b / a;

    }
      std::cout << sum << std::endl;
      Z.push_back(sum);
  }

#endif

  return 0;
}
