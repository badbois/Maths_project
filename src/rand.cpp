// maybe put a function in argument too...

#include "rand.hpp"
#include "include/random.hpp"
#include <cmath>
#include <iostream>

float p = 0.5f;
float alpha = 0.5f;
float shape_markov = 0.3f;

void set_random_parameters(int difficulty) {
  if (difficulty == 1) {
    // jsp si c'est + ou - dur si tu tournes ou pas, à voir
    p = 0.1f;
    alpha = 0.5f;
    shape_markov = 0.1f;
  }
}

int from_random_to_value(const int nb_values, const float rand) {
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

int bernoulli(float p) {
  float rand = random_float(0.f, 1.f);
  return rand < p ? 1 : 0;
}

int rademacher(float alpha) {
  float rand = random_float(0.f, 1.f);
  return rand < alpha ? 1 : -1;
}

int markov(int latest_shape) {
  float rand = random_float(0.f, 1.f);
  if (rand < shape_markov) {
    return latest_shape;
  }
  if (latest_shape == 0) {
    return 1 + random_uniform(2);
  } else if (latest_shape == 1) {
    return 2 * random_uniform(2);
  } else {
    return random_uniform(2);
  }
}

/*pourrait peut être être utile pour les combos, si après plusieurs bons coups
on trouve dans un tps inférieur à ce tps, alors meilleur combo. A utiliser si
vrm le prof veut une loi exponentielle*/
float time_until_combo(const float average_combo_time) {
  float rand = random_float(0.f, 1.f);
  return -average_combo_time * log(1 - rand);
}

int random_rotation_direction() {
  int rand = bernoulli(p);
  return rand == 0 ? 0 : rademacher(alpha);
}

int random_shape(const int nb_of_shapes) {
  float rand = random_float(0.f, 1.f);
  return random_uniform(nb_of_shapes, rand);
}

int random_color(const int nb_of_colors) {
  float rand = random_float(0.f, 1.f);
  return from_random_to_value(nb_of_colors, rand);
}

int random_position(const int nb_of_objects_by_line) {
  float rand = random_float(0.f, 1.f);
  return from_random_to_value(nb_of_objects_by_line, rand);
}