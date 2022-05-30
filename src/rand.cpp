// maybe put a function in argument too...

#include "rand.hpp"
#include "include/random.hpp"
#include "stats.hpp"
#include <cmath>
#include <iostream>
#include <math.h>

struct RandomParameters {
  float p = 0.5f;
  float shape_markov = 0.5f;
  int difficulty = 0;
  float sigma = 5.f;
  float gamma = 3.f;
  std::vector<float> gaussian_probabilities;

  RandomParameters() : gaussian_probabilities(7){};
};

RandomParameters parameters;

void set_gaussian_probabilities() {
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
    parameters.shape_markov = 0.2f;
    parameters.difficulty = 1;
    parameters.sigma = 0.2f;
    parameters.gamma = 1.f;
  } else {
    parameters.p = 0.5f;
    parameters.shape_markov = 0.6f;
    parameters.difficulty = 0;
    parameters.sigma = 5.f;
    parameters.gamma = 3.f;
  }
}

void display_statistics() {
  statistic(parameters.p, parameters.alpha, parameters.gamma,
            parameters.difficulty, parameters.gaussian_probabilities);
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

int markov(const int latest_shape) {
  float rand = random_float(0.f, 1.f);
  if (rand < parameters.shape_markov) {
    return latest_shape;
  }
  if (latest_shape == 0) {
    // random between 1 and 2
    return 1 + random_uniform(2);
  } else if (latest_shape == 1) {
    // random between 0 and 2
    return 2 * random_uniform(2);
  } else {
    // random between 0 and 1
    return random_uniform(2);
  }
}

int random_shape(const int nb_of_shapes) {
  return random_uniform(nb_of_shapes);
}

float time_until_combo() {
  float rand = random_float(0.f, 1.f);
  rand = -parameters.gamma * log(1 - rand);
  return rand;
}

float gaussian_rotation() {
  float u1 = random_float(0.f, 1.f);
  float u2 = random_float(0.f, 1.f);
  while (u1 == 0.f) {
    u1 = random_float(0.f, 1.f);
  }
  while (u2 == 0.f) {
    u2 = random_float(0.f, 1.f);
  }
  return sqrt(-2 * log(u1)) * sin(2 * 3.14 * u2);
}

float random_rotation() {
  int rand = bernoulli(parameters.p);
  return rand == 0 ? 0 : gaussian_rotation();
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