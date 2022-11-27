#ifndef _CRITICAL_UTIL_H
#define _CRITICAL_UTIL_H

#include <set>
#include <math.h>

namespace critical {

template <class T>
inline bool contains(const std::set<T>& set, const T& elem) {
  return set.find(elem) != set.end();
};

template <class T>
inline void removeIfPresent(std::set<T>& set, const T& elem) {
  auto it = set.find(elem);
  if (it != set.end()) {
    set.erase(it);
  }
};

inline bool isZero(double val) {
  return std::abs(val) < 1e-6;
};

struct Empty {};

const double INF = std::numeric_limits<double>().infinity();



}


#endif 