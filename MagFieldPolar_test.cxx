/*
  Copyright (C) 2002-2020 CERN for the benefit of the ATLAS collaboration
*/

#include "BFieldCache.h"
#include "BFieldZone.h"
#include <iostream>

constexpr int nmeshz{ 4 };
constexpr int nmeshr{ 5 };
constexpr int nmeshphi{ 6 };
constexpr int nfield = nmeshz * nmeshr * nmeshphi;

using dbl = std::numeric_limits<double>;

struct BFieldData
{

  double fieldz[nfield] = {
    19487, 19487, 19488, 19488, 19487, 19487, 19531, 19531, 19532, 19532, 19531,
    19531, 6399,  6400,  6400,  6400,  6399,  -1561, -1561, -1560, -1560, -1560,
    -1561, -1516, -1516, -1515, -1515, -1516, -1516, 20310, 20310, 20311, 20311,
    20311, 20310, 20329, 20329, 20329, 20330, 20329, 20329, 7172,  7173,  7173,
    7172,  7172,  -814,  -814,  -813,  -812,  -813,  -814,  -795,  -795,  -794,
    -793,  -794,  -795,  20310, 20310, 20311, 20312, 20311, 20310, 20329, 20329,
    20330, 20330, 20330, 20329, 7172,  7172,  7173,  7173,  7173,  7172,  -813,
    -813,  -812,  -812,  -813,  -813,  -794,  -794,  -793,  -793,  -793,  -794,
    19487, 19487, 19488, 19488, 19488, 19487, 19531, 19531, 19532, 19532, 19532,
    19531, 6400,  6399,  6400,  6401,  6400,  6400,  -1561, -1561, -1560, -1559,
    -1560, -1561, -1516, -1516, -1515, -1515, -1515, -1516, -1516, -1516
  };

  double fieldr[nfield] = {
    -1357, -1356, -1353, -1354, -1354, -1357, -1366, -1366, -1362, -1363, -1363,
    -1366, -1378, -1374, -1375, -1375, -1378, -1388, -1388, -1385, -1386, -1386,
    -1388, -1394, -1394, -1390, -1391, -1391, -1394, -318,  -318,  -314,  -315,
    -316,  -318,  -321,  -321,  -317,  -318,  -319,  -321,  -325,  -321,  -322,
    -322,  -325,  -328,  -328,  -324,  -325,  -326,  -328,  -330,  -331,  -326,
    -327,  -328,  -330,  312,   312,   316,   315,   315,   312,   315,   315,
    319,   318,   318,   315,   319,   318,   323,   322,   321,   319,   322,
    322,   326,   325,   325,   322,   324,   324,   328,   327,   327,   324,
    1351,  1351,  1356,  1354,  1354,  1351,  1360,  1360,  1365,  1363,  1363,
    1360,  1372,  1372,  1377,  1375,  1375,  1372,  1383,  1383,  1387,  1386,
    1386,  1383,  1388,  1388,  1393,  1391,  1391,  1388,  1388,  1388
  };

  double fieldphi[nfield] = {
    -2, 7,  3,  1,  6, -2, -2, 7, 3,  1,  6, -2, -2, 3, 1,  6,  -2, -2, 7, 3,
    1,  6,  -2, -2, 7, 3,  1,  6, -2, -1, 7, 3,  1,  6, -1, -1, 7,  3,  1, 6,
    -1, -1, 3,  1,  6, -1, -1, 7, 3,  1,  6, -1, -1, 8, 3,  1,  6,  -1, 1, 7,
    3,  2,  6,  1,  1, 7,  3,  2, 6,  1,  1, 7,  3,  2, 6,  1,  1,  7,  3, 2,
    6,  1,  0,  8,  3, 2,  6,  0, 2,  7,  3, 2,  6,  2, 2,  7,  3,  2,  6, 2,
    2,  7,  3,  2,  6, 2,  2,  7, 3,  2,  6, 2,  2,  8, 3,  2,  6,  2,  2, 2
  };

  double meshr[nmeshr] = { 1200, 1225, 1250, 1275, 1300 };
  double meshphi[nmeshphi] = { 0, 1.25664, 2.51327, 3.76991, 5.02655, 6.28318 };
  double meshz[nmeshz] = { -1400, -466.93, 466.14, 1400 };

  int id{ 5 };
  double zmin{ -1400 };
  double zmax{ 1400 };
  double rmin{ 1200 };
  double rmax{ 1300 };
  double phimin{ 0 };
  double phimax{ 6.28319 };
  double bscale{ 1e-07 };

  BFieldZone zone;

  BFieldData()
    : zone(id, zmin, zmax, rmin, rmax, phimin, phimax, bscale)
  {
    zone.reserve(nmeshz, nmeshr, nmeshphi);
    for (int j = 0; j < nmeshz; j++) {
      zone.appendMesh(0, meshz[j]);
    }

    for (int j = 0; j < nmeshr; j++) {
      zone.appendMesh(1, meshr[j]);
    }

    for (int j = 0; j < nmeshphi; j++) {
      zone.appendMesh(2, meshphi[j]);
    }

    for (int j = 0; j < nfield; j++) {
      BFieldVector<short> field(fieldz[j], fieldr[j], fieldphi[j]);
      zone.appendField(field);
    }

    // build (trivial) look up table for zone
    zone.buildLUT();
  }
};

int
main()
{
  double z0 = 0;
  double r0 = 1200;
  double phi0 = 1.6;
  double xyz[3] = { 0, 0, 0 };
  double bxyz[3] = { 0, 0, 0 };
  double derivatives[9] = { 0 };
  BFieldData data{};
  BFieldCache cache3d;
  
  for (unsigned int i = 0; i < 95; ++i) {
    double r1 = r0 + 5 + i * 1.;
    std::cout << '\n' << " ----  r " << r1 << " ----" << '\n';
    // Here us what tracking passes
    xyz[0] = r1 * cos(phi0);
    xyz[1] = r1 * sin(phi0);
    xyz[2] = z0;
    // So let pretend we do not know about it
    const double x = xyz[0];
    const double y = xyz[1];
    const double z = xyz[2];
    const double r = std::sqrt(x * x + y * y);
    const double phi = std::atan2(y, x);

    std::cout << " xyz " << x << " " << y << " " << z << '\n';
    std::cout << " r,phi " << r << " " << phi << " " << '\n';
    // test if initialised and the cache is valid
    if (!cache3d.inside(z, r, phi)) {
      std::cout << " step " << i << " out side" << '\n';
      // cache is invalid -> refresh cache
      data.zone.getCache(z, r, phi, cache3d, 1);
    }else{
    std::cout << " step " << i << " in side" << '\n';
    }
    cache3d.getB(xyz, r, phi, bxyz, derivatives);
  }
  return 0;
}

