// maybe put a function in argument too...

#include "Rand.hpp"
#include "include/random.hpp"
#include <iostream>

int fromRandomToValue(int nb_values, float rand) {
  int i = 0;
  while (rand > static_cast<float>(i + 1) / nb_values && i < nb_values) {
    i++;
  }
  return i;
}

int randomUniform(int nb_values) {
  float rand = randomFloat(0., 1.);
  return fromRandomToValue(nb_values, rand);
}