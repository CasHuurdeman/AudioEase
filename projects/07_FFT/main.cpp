//
// Created by cashu on 01/12/2025.
//
#include <iostream>
#include <array>
#include "FFT.h"

const int j = -1;
// const double PI = 4*atan(1);


class Complex
{
public:
  Complex() = default;
  Complex(double a, double b)
  {
    r = sqrt(a * a + b * b);
    phi = atan2(b, a);

    re = a;
    im = b;
  }
  ~Complex() = default;

  void multiplyP(Complex a, Complex b)
  {
    r = a.r*b.r;
    phi = a.phi+b.phi;

    re = r*cos(phi);
    im = r*sin(phi);
  }


  double arg() const { return phi; }
  double abs() const { return r; }
  double real() const { return re; }
  double imag() const { return im; }

  void calcC(){
    re = r*cos(phi);
    im = r*sin(phi);}

  void calcP(){
    r = sqrt(im * im + re * re);
    phi = atan2(re, im);}

  double re = 0;
  double im = 0;
  double r = 0;
  double phi = 0;
};


int main()
{
  const int fftSize = 8;
  std::array<double, fftSize> X{1,0,0,0,0,0,0,0};
  std::array<double, fftSize> Y{1,0,0,0,0,0,0,0}; //when this is a pulse, nothing happens

  std::array<double, fftSize> Z{0,0,0,0,0,0,0,0};


  realfft_packed(&X[0], fftSize);
  realfft_packed(&Y[0], fftSize);

  Z[0] = X[0] * Y[0];
  for (int i = 2; i < fftSize; i+=2) {
    Complex x(X[i],X[i+1]);
    Complex y(Y[i],Y[i+1]);
//==============================================
//    Playground x,y




//==============================================
    Complex z;
    z.multiplyP(x,y);

//==============================================
//    Playground Z

    // z.phi = 0;
    z.r *= 2;
    z.calcC();


//==============================================

    Z[i] = z.real();
    Z[i+1] = z.imag();

    // std::cout << abs(z) << "," << arg(z) << "               " << real(z) << "," << imag(z) << "\n";
  }
  Z[1] = X[1]*Y[1];

  irealfft_packed(&Z[0], fftSize);

  for (double i : Z) {
    std::cout << i << std::endl;
  }

  return 0;
}
