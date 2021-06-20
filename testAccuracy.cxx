#include "CartesianToPolar.h"
#include <cmath>
#include <iostream>
using dbl = std::numeric_limits<double>;

int
main()
{
  double r0{ 1250 }, phi0{M_PI};
  fastCache cache1{};
  fastCache cache2{};
  for (unsigned int i = 0; i < 100; ++i) {
    double r = r0 + 5 + i * 1;
    double phi = phi0 - i*1e-3;
    cartesian init{ r * std::cos(phi), r * std::sin(phi) };
    
    polar exact = precisePol(init);
    polar fast1 = fastPol(init, cache1);
    polar fast2 = fastPol1(init, cache2);
    //
    std::cout << " =======================" << '\n';
    std::cout << " VERSION 1" << '\n';
    std::cout << " exact r : " << exact.r << " fast 1 r : " << fast1.r
              << " diff " << std::abs(exact.r - fast1.r) << '\n';
 
    std::cout << " exact phi : " << exact.phi << " fast 1 phi : " << fast1.phi
              << " diff " << std::abs(exact.phi - fast1.phi)
              << '\n';
    //
    std::cout << " VERSION 2" << '\n';
    std::cout << " exact r : " << exact.r << " fast 2 r : " << fast2.r
              << " diff " << std::abs(exact.r - fast2.r)  << '\n';
 
    std::cout << " exact phi : " << exact.phi << " fast 2 phi : " << fast2.phi
              << " diff " << std::abs(exact.phi - fast2.phi)
              << '\n';
    std::cout  << '\n';
 
  }
  return 0;
}
