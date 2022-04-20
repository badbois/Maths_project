// maybe put a function in argument too...

#include "rand.hpp"
#include "include/random.hpp"
#include <cmath>
#include <iostream>

int from_random_to_value(const int nb_values,const float rand) {
  int i = 0;
  while (rand > static_cast<float>(i + 1) / nb_values && i < nb_values) {
    i++;
  }
  return i;
}

int random_uniform(const int nb_values) {
  float rand = random_float(0.f, 1.f);
  return from_random_to_value(nb_values, rand);
}

/*pourrait peut être être utile pour les combos, si après plusieurs bons coups
on trouve dans un tps inférieur à ce tps, alors meilleur combo. A utiliser si
vrm le prof veut une loi exponentielle*/
float time_until_combo(const float average_combo_time) {
  float rand = random_float(0.f, 1.f);
  return -average_combo_time * log(1 - rand);
}

int random_rotation_direction() {
  float rand = random_float(0.f, 1.f);
  // en vrai on fera Bernoulli et Rademacher
  return from_random_to_value(3, rand) - 1;
}

int random_shape(const int nb_of_shapes) {
  float rand = random_float(0.f, 1.f);
  return from_random_to_value(nb_of_shapes, rand);
}

int random_color(const int nb_of_colors) {
  float rand = random_float(0.f, 1.f);
  return from_random_to_value(nb_of_colors, rand);
}

int random_position(const int nb_of_objects_by_line) {
  float rand = random_float(0.f, 1.f);
  return from_random_to_value(nb_of_objects_by_line, rand);
}