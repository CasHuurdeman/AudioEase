//
// Created by cashu on 12/11/2025.
//
#include "reflectionManager.h"
#include <iostream>

int main() {
  ReflectionManager reflection_manager;


  return 0;
}

// int main(){
//   Grid grid;
//
//
//   //AANTAL SPIEGELKAMERS BIJ 4E ORDE
//
// //1d
//   int n0 = 0;
//   for (int i = 0; i <= 6; i++) {
//     n0 += 2;
//   }
//
// //2d --> deze klopt
//   int n1 = 0;
//   for (int i = 0; i <= 6; i++) {
//     n1 += 4*i ;
//     // std::cout << n1 << std::endl;
//   }
//
//
// //WERKT OOK NIET
//   int maxOrde = 4;
//   int dimensie = 3;
//   int n = 0;
//   int orde = 1;
//   int add = 0;
//
//   std::cout << "Dimensie: " << dimensie << std::endl;
//   for (int i = 0; i <= maxOrde; i++) {
//     add += (dimensie-1)*i*4;
//     n = dimensie * orde * 2 + add;
//     orde++;
//     // std::cout << n << std::endl;
//   }
//
//
//   return 0;
// }
