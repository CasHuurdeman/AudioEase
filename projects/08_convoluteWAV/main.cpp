//
// Created by cashu on 01/12/2025.
//
#include <iostream>
#include <vector>
#include <array>
#include <complex>
#include "FFT.h"
#include "readWAV.h"
#include "writeToWAV.h"
#include "speedTest.h"

//FFT CONVOLUTION --> 0
//FFT DECONVOLUTION --> 1
//NON-FFT CONVOLUTION --> 2
#define state 1
  // std::array<double, fftSize*2> X{};
  // X.fill(0);
  //
  // memcpy(&X, &signal, sizeof(signal));
std::string sourceDir = SOURCE_DIR;


int main()
{
  //TODO - these are not here now
  ReadWAV audio("convolution.wav", sourceDir);
  ReadWAV impulse("test.wav", sourceDir);
  WriteToWAV convolution("deconvolve", sourceDir, 48000);

  audio.readWavFile();
  impulse.readWavFile();

  //TODO - FFTSIZE SHOULD BE 2^X
  const int fftSize = 65536;
  std::vector<float> fX(fftSize, 0);
  std::vector<float> fY(fftSize, 0);
  std::vector<double> Z(fftSize);

  memcpy(&fX[0], &audio.getSamplesL()[0], audio.getNumSamples());
  memcpy(&fY[0], &impulse.getSamplesL()[0], impulse.getNumSamples());


  std::vector<double> X;
  std::vector<double> Y;


  for (float sample : fX) { X.push_back(sample);}
  for (float sample : fY) { Y.push_back(static_cast<double>(sample));}


#if state == 0
  realfft_packed(&X[0], fftSize);
  realfft_packed(&Y[0], fftSize);

  Z[0] = X[0] * Y[0];
  for (int i = 2; i < fftSize; i+=2) {
    std::complex z1(X[i], X[i+1]);
    std::complex z2(Y[i], Y[i+1]);

    std::complex z = z1*z2;
    Z[i] = real(z);
    Z[i+1] = imag(z);
  }
  Z[1] = X[1]*Y[1];

  //Normalising
  for (int i = 0; i < fftSize; i++) {
    Z[i] *= fftSize;
  }

  irealfft_packed(&Z[0], fftSize);

#elif state == 1

  realfft_packed(&X[0], fftSize);
  realfft_packed(&Y[0], fftSize);

  for (int i = 0; i < fftSize; i++)
  {
      Y[i] += 0.00000001;
  }


  Z[0] = X[0] / Y[0];
  for (int i = 2; i < fftSize; i+=2) {
    std::complex z1(X[i], X[i+1]);
    std::complex z2(Y[i], Y[i+1]);

    std::complex z = z1/z2;
    Z[i] = real(z);
    Z[i+1] = imag(z);
  }
  Z[1] = X[1]/Y[1];

  //Normalising
  for (int i = 0; i < fftSize; i++) {
    Z[i] /= fftSize;
  }

  irealfft_packed(&Z[0], fftSize);

#else
  SpeedTest speed_test;
  speed_test.start();

  for(int n = 0; n < fftSize; n++)
  {
    double sum = 0;
    for(int k = 0; k < fftSize; k++)
    {
      double a;
      if (n-k < 0 || fftSize <= n)  a = 0;
      else  a = X[n-k];

      double b;
      if (k < 0 || fftSize <= k) b = 0;
      else b = Y[k];

      sum += b * a;

    }
    // std::cout << sum << std::endl;
    Z[n] = sum;
  }

  speed_test.printSpeed();

#endif

  for (int i = 0; i < fftSize; i++) {
    convolution.write(Z[i],Z[i]);
  }

  return 0;
}
