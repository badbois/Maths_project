#pragma once

#include <vector>

template <class T> T fromRandomToValue(std::vector<T> values) {
  float rand = 0.5; // random function
  int i = 0;
  int nb_values = values.size();
  while (rand > static_cast<float>(i / nb_values) && i < nb_values - 1) {
    i++;
  }
  return values[i];
}
