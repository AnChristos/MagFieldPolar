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
  double prevInvR2{ 0. };
  double prevPhi{ 0. };
  int steps{ -1 };
};

// usiang atan
inline polar
precisePol(const cartesian& cart)
{
  return polar{ std::sqrt(cart.x * cart.x + cart.y * cart.y),
                std::atan2(cart.y, cart.x) };
}

// using acos (not faster than using atan)
inline polar
altPol(const cartesian& cart)
{
  const double R = std::sqrt(cart.x * cart.x + cart.y * cart.y);
  return { R, std::copysign(std::acos(cart.x / R), cart.y) };
}

// use accurate r and expansion for dphi
inline polar
fastPol(const cartesian& cart, fastCache& cache, bool forceReset = false)
{
  polar result;
  const double newR2 = cart.x * cart.x + cart.y * cart.y;
  const double newR = std::sqrt(newR2);
  if (cache.steps == -1 || cache.steps > 4 || forceReset) {
    result = { newR, std::atan2(cart.y, cart.x) };
    cache.steps = 0;
  } else {
    // Approximation for phi
    const double invR2 = cache.prevInvR2;
    const double dX = cart.x - cache.prevX;
    const double dY = cart.y - cache.prevY;
    const double firstPhiTerm = (-cart.y * dX + cart.x * dY) * invR2;
    double newPhi = cache.prevPhi + firstPhiTerm;
    if (newPhi > M_PI) {
      newPhi -= 2. * M_PI;
    }
    result = { newR, newPhi };
  }
  cache.prevY = cart.y;
  cache.prevX = cart.x;
  cache.prevInvR2 = 1. / (newR2);
  cache.prevPhi = result.phi;
  ++cache.steps;
  return result;
}

// use accurate r and expansion for dphi
inline polar
fastPol1(const cartesian& cart, fastCache& cache, bool forceReset = false)
{
  polar result;
  const double newR2 = cart.x * cart.x + cart.y * cart.y;
  const double newR = std::sqrt(newR2);
  if (cache.steps == -1 || cache.steps > 10 || forceReset) {
    result = { newR, std::atan2(cart.y, cart.x) };
    cache.steps = 0;
  } else {
    // Approximation for phi
    const double invR2 = cache.prevInvR2;
    const double dX = cart.x - cache.prevX;
    const double dY = cart.y - cache.prevY;
    const double firstPhiTerm = (-cart.y * dX + cart.x * dY) * invR2;
    double newPhi = cache.prevPhi + firstPhiTerm;
    if (newPhi > M_PI) {
      newPhi -= 2. * M_PI;
    }
    result = { newR, newPhi };
  }
  cache.prevY = cart.y;
  cache.prevX = cart.x;
  cache.prevInvR2 = 1. / (newR2);
  cache.prevPhi = result.phi;
  ++cache.steps;
  return result;
}
