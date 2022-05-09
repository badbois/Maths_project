#pragma once

#include <random>

/// Returns a random int between min (included) and max (included)
template <typename T> inline T random_int(const T min, const T max) {
  static std::default_random_engine generator{std::random_device{}()};
  std::uniform_int_distribution<T> distribution{min, max};
  return distribution(generator);
}

/// Returns a random real between min (included) and max (included)
// template <typename T> inline T random_float(const T min,const T max) {
//   static std::default_random_engine generator{std::random_device{}()};
//   std::uniform_real_distribution<T> distribution{min, max};
//   return distribution(generator);
// }
float random_float(const float min,const float max) {
  static std::default_random_engine generator{std::random_device{}()};
  std::uniform_real_distribution<float> distribution{min, max};
  return distribution(generator);
}