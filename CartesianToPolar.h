#include <cmath>
struct cartesian
{
  double x{ 0. };
  double y{ 0. };
};

struct polar
{
  double r{ 0. };
  double phi{ 0. };
};

struct fastCache
{
  double prevX{ 0. };
  double prevY{ 0. };
  double prevR{ 0. };
  double prevPhi{ 0. };
  int steps{ -1 };
};

inline polar
precisePol(const cartesian& cart)
{
  return polar{ std::sqrt(cart.x * cart.x + cart.y * cart.y),
                std::atan2(cart.y, cart.x) };
}

inline polar
altPol(const cartesian& cart)
{
  const double R = std::sqrt(cart.x * cart.x + cart.y * cart.y);
  return { R, std::copysign(std::acos(cart.x / R), cart.y) };
}

inline polar
fastPol(const cartesian& cart, fastCache& cache, bool forceReset = false)
{
  polar result;
  if (cache.steps == -1 || cache.steps > 10 || forceReset) {
    result = precisePol(cart);
    cache.steps = 0;
  } else {
    const double invR = 1. / cache.prevR;
    const double invR2 = invR * invR;
    // The R we can always do exact not too expensive
    const double newR = std::sqrt(cart.x * cart.x + cart.y * cart.y);
    // Approximation for phi
    const double dX = cart.x - cache.prevX;
    const double dY = cart.y - cache.prevY;
    const double firstPhiterm = -cart.y * invR2 * dX + cart.x * invR2 * dY;
    double newPhi = cache.prevPhi - firstPhiterm;
    if (newPhi > M_PI) {
      newPhi -= 2. * M_PI;
    }
    result = { newR, newPhi };
  }
  cache.prevY = cart.y;
  cache.prevX = cart.x;
  cache.prevR = result.r;
  cache.prevPhi = result.phi;
  ++cache.steps;
  return result;
}

