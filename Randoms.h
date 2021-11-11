#ifndef AOIN_RANDOMS_H
#define AOIN_RANDOMS_H

#include <mutex>
#include <thread>
#include <vector>

#include "Graph.h"

#include <cmath>
#include <cstdlib>
#include <limits>
#include <random>

namespace re {
class Randoms {

public:
  Randoms() = default;

  double uniform();

  template <typename T> auto random_in_range(T min, T max) {
    static std::mt19937 mt(rand_device());
    static std::uniform_int_distribution<T> pick(min, max);

    return pick(mt);
  }

private:
  std::random_device rand_device;
};
} // namespace re

#endif // AOIN_RANDOMS_H