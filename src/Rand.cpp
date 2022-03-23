// maybe put a function in argument too...

#include "Rand.hpp"
#include "include/random.hpp"
#include <cmath>
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

/*pourrait peut être être utile pour les combos, si après plusieurs bons coups
on trouve dans un tps inférieur à ce tps, alors meilleur combo. A utiliser si
vrm le prof veut une loi exponentielle*/
float timeUntilCombo(float averageComboTime) {
  float rand = randomFloat(0., 1.);
  return -averageComboTime * log(1 - rand);
}