#include "CartesianToPolar.h"
#include <cmath>
#include <iostream>
using dbl = std::numeric_limits<double>;

int
main()
{
  double r0{ 1250 }, phi{ 1.6 };
  fastCache cache{};
  for (unsigned int i = 0; i < 100; ++i) {
    double r1 = r0 + 5 + i * 1;
    cartesian init{ r1 * std::cos(phi), r1 * std::sin(phi) };
    polar exact = precisePol(init);
    polar fast = fastPol(init, cache);
    polar alt = altPol(init);
    std::cout << " exact r : " << exact.r << " fast r : " << fast.r
              << " % diff " << std::abs(exact.r - fast.r) / exact.r << '\n';
    std::cout << " exact phi : " << exact.phi << " fast phi : " << fast.phi
              << " % diff " << std::abs(exact.phi - fast.phi) / exact.phi
              << '\n';
    std::cout << " exact r : " << exact.r << " alt r : " << alt.r
              << " % diff " << std::abs(exact.r - alt.r) / exact.r << '\n';
    std::cout << " exact phi : " << exact.phi << " fast phi : " << alt.phi
              << " % diff " << std::abs(exact.phi - alt.phi) / exact.phi
              << '\n';
 
  }
  return 0;
}
