// maybe put a function in argument too...

#include "rand.hpp"
#include "include/random.hpp"
#include "stats.hpp"
#include <cmath>
#include <iostream>
#include <math.h>

struct RandomParameters {
  float p = 0.5f;
  float alpha = 0.9f;
  float shape_markov = 0.5f;
  int difficulty = 0;
  float sigma = 5.f;
  float lambda = 1.f;
  std::vector<float> gaussian_probabilities;

  RandomParameters() : gaussian_probabilities(7){};
};

Statistics stats;
RandomParameters parameters;

void set_gaussian_probabilities() {
  // on va essayer d'automatiser plus tard mais jsp si on la droit d'utiliser la
  // loi gaussienne juste pour calculer les proba.. je demanderai au prof
  parameters.gaussian_probabilities[0] = 0.04775;
  parameters.gaussian_probabilities[1] = 0.1109;
  parameters.gaussian_probabilities[2] = 0.2108;
  parameters.gaussian_probabilities[3] = 0.2611;
  parameters.gaussian_probabilities[4] = 0.2108;
  parameters.gaussian_probabilities[5] = 0.1109;
  parameters.gaussian_probabilities[6] = 0.04775;
}

void set_difficulty(const int difficulty_gamer) {
  if (difficulty_gamer == 1) {
    // jsp si c'est + ou - dur si tu tournes ou pas, à voir
    parameters.p = 0.9f;
    parameters.alpha = 0.5f;
    parameters.shape_markov = 0.1f;
    parameters.difficulty = 1;
    parameters.sigma = 0.2f;
    parameters.lambda = 0.5f;
  } else {
    parameters.p = 0.5f;
    parameters.alpha = 0.9f;
    parameters.shape_markov = 0.5f;
    parameters.difficulty = 0;
    parameters.sigma = 5.f;
    parameters.lambda = 1.f;
  }
}

void reload() {
  for (int i = 0; i < stats.positions.size(); i++) {
    stats.positions[i] = 0;
  }
  stats.bernoulli = 0;
  stats.rademacher = 0;
  stats.nb_objects = 0;
  stats.rounds = 0;
  stats.exp.clear();
}

void add_positions_stats(int value) { stats.positions[value]++; }

void add_rotation_stats(int rotation) {
  if (rotation == 1) {
    stats.bernoulli++;
    stats.rademacher++;
  }
  if (rotation == -1) {
    stats.bernoulli++;
  }
}

void update_stats(int posx, int posy, int rotation) {
  add_positions_stats(posx);
  add_positions_stats(posy);
  add_rotation_stats(rotation);
  stats.nb_objects++;
}

void add_round_stats() { stats.rounds++; }

void display_statistics() {
  statistic(stats, parameters.p, parameters.alpha, parameters.lambda,
            parameters.difficulty, parameters.gaussian_probabilities);
  reload();
};

int random_uniform(const int nb_values) {
  float rand = random_float(0.f, 1.f);
  int i = 0;
  while (rand > static_cast<float>(i + 1) / nb_values && i < nb_values) {
    i++;
  }
  return i;
}

int random_color(const int nb_of_colors, const int unique_color) {
  float rand = random_float(0.f, 1.f);
  float color_difficulty = 1.f / nb_of_colors;
  if (parameters.difficulty == 1) {
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

int random_color(const int nb_of_colors) {
  return random_uniform(nb_of_colors);
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
  if (rand < parameters.shape_markov) {
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
float time_until_combo() {
  float rand = random_float(0.f, 1.f);
  rand = -parameters.lambda * log(1 - rand);
  stats.exp.push_back(rand);
  return rand;
}

int random_rotation_direction() {
  int rand = bernoulli(parameters.p);
  return rand == 0 ? 0 : rademacher(parameters.alpha);
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
  if (parameters.difficulty == 1) {
    return random_uniform(7);
  } else {
    return from_random_to_value(parameters.gaussian_probabilities);
  }
}