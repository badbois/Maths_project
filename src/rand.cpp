// maybe put a function in argument too...

#include "rand.hpp"
#include "include/random.hpp"
#include <cmath>
#include <iostream>
#include <math.h>

float p = 0.5f;
float alpha = 0.5f;
float shape_markov = 0.5f;
int difficulty = 0;
float sigma = 5.f;

void set_difficulty(const int difficulty_gamer) {
  if (difficulty_gamer == 1) {
    // jsp si c'est + ou - dur si tu tournes ou pas, à voir
    p = 0.1f;
    alpha = 0.5f;
    shape_markov = 0.1f;
    difficulty = 1;
    sigma = 0.2f;
  }
}

int random_color(const int nb_of_colors, const int unique_color) {
  float rand = random_float(0.f, 1.f);
  float color_difficulty = 1.f / nb_of_colors;
  if (difficulty == 1) {
    color_difficulty = 0.8;
  }
  int color = unique_color;
  if (rand > color_difficulty) {
    while (color == unique_color) {
      color = random_uniform(nb_of_colors);
    }
  }
  return color;
}

int random_uniform(const int nb_values) {
  float rand = random_float(0.f, 1.f);
  int i = 0;
  while (rand > static_cast<float>(i + 1) / nb_values && i < nb_values) {
    i++;
  }
  return i;
}

int bernoulli(const float p) {
  float rand = random_float(0.f, 1.f);
  return rand < p ? 1 : 0;
}

int rademacher(const float alpha) {
  float rand = random_float(0.f, 1.f);
  return rand < alpha ? 1 : -1;
}

// for unique object
int markov(const int latest_shape) {
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

// for other objects
int random_shape(const int nb_of_shapes) {
  return random_uniform(nb_of_shapes);
}

// for combos
float time_until_combo(const float average_combo_time) {
  float rand = random_float(0.f, 1.f);
  return -average_combo_time * log(1 - rand);
}

int random_rotation_direction() {
  int rand = bernoulli(p);
  return rand == 0 ? 0 : rademacher(alpha);
}

void set_gaussian_probabilities(std::vector<float> &probabilities) {
  // on va essayer d'automatiser plus tard mais jsp si on la droit d'utiliser la
  // loi gaussienne juste pour calculer les proba.. je demanderai au prof
  probabilities[0] = 0.05;
  probabilities[1] = 0.11;
  probabilities[2] = 0.21;
  probabilities[3] = 0.26;
  probabilities[4] = 0.21;
  probabilities[5] = 0.11;
  probabilities[6] = 0.05;
}

int from_random_to_value(std::vector<float> probabilities) {
  float rand = random_float(0.f, 1.f);
  int i = 0;
  float proba = probabilities[0];
  while (rand > proba && i < probabilities.size() - 1) {
    proba += probabilities[i + 1];
    i++;
  }
  return i;
}

int random_position(const int nb_of_objects_by_line) {
  if (difficulty == 1) {
    return random_uniform(7);
  } else {
    std::vector<float> probabilities(7);
    set_gaussian_probabilities(probabilities);
    return from_random_to_value(probabilities);
  }
}