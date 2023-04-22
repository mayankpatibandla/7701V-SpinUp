#pragma once
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "v5.h"
#include "v5_vcs.h"

#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)

using namespace vex;

template <typename T> T sgn(const T &val) {
  return (T(0) < val) - (val < T(0));
}
template <typename T> T clamp(const T &n, const T &lower, const T &upper) {
  return std::max(lower, std::min(n, upper));
}