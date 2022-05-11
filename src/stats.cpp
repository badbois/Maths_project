#include "stats.hpp"
#include "math.h"
#include <iostream>

struct Statistics {
  std::vector<int> positions;
  int bernoulli = 0;
  int rademacher = 0;
  int nb_objects = 0;
  std::vector<float> exp;
  int rounds = 0;
  Statistics() : positions(7, 0){};
};

Statistics stats;

// update statistics

void reload() {
  for (int i = 0; i < stats.positions.size(); i++) {
    stats.positions[i] = 0;
  }
  stats.nb_objects = 0;
  stats.rounds = 0;
  stats.exp.clear();
}

void add_positions_stats(int value) { stats.positions[value]++; }

void add_exp_stats(float rand) { stats.exp.push_back(rand); }

void update_stats(int posx, int posy, int rotation) {
  add_positions_stats(posx);
  add_positions_stats(posy);
  stats.nb_objects++;
}

void add_round_stats() { stats.rounds++; }

// display statistics

void draw_line(int nb_line, int nb) {
  std::cout << nb_line << " : ";
  for (int i = 0; i < nb; i++) {
    std::cout << "*";
  }
  std::cout << std::endl;
}

void display_exp(std::vector<float> exp, float lambda) {
  float mean = 0;
  for (int i = 0; i < exp.size(); i++) {
    mean += exp[i];
  }
  mean /= exp.size();
  float standard_deviation = 0;
  for (int i = 0; i < exp.size(); i++) {
    standard_deviation += (exp[i] - mean) * (exp[i] - mean);
  }
  standard_deviation = sqrt(standard_deviation / exp.size());

  std::cout << "Sur un échantillon de " << exp.size() << "clics :" << std::endl;

  std::cout << "La moyenne de temps avant le prochain combo est : " << mean
            << std::endl;
  std::cout << "Théoriquement, cette moyenne était de : " << lambda
            << std::endl;

  std::cout << "L'écart type associé est : " << standard_deviation << std::endl;
  std::cout << "Théoriquement, cet écart type était de : " << lambda
            << std::endl;

  std::cout << std::endl;
}

void display_uniform_position(std::vector<int> positions, int nb_objects,
                              int rounds, int difficulty,
                              std::vector<float> gaussian_probabilities) {
  int nb_positions = positions.size();
  int nb_positions_attributed = 0;
  float mean = 0;
  float standard_deviation = 0;
  std::cout << "Diagramme des positions (x et y confondus) :" << std::endl;
  for (int i = 0; i < nb_positions; i++) {
    draw_line(i, static_cast<int>(positions[i] / (rounds + 1)));
  }
  std::cout << std::endl;
  std::cout << "Diagramme des positions théorique :" << std::endl;
  if (difficulty == 1) {
    for (int i = 0; i < nb_positions; i++) {
      draw_line(i, 2 * nb_objects / (nb_positions * (rounds + 1)));
      mean += i * positions[i];
      nb_positions_attributed += positions[i];
    }
    mean /= nb_positions_attributed;
    for (int i = 0; i < nb_positions; i++) {
      standard_deviation += positions[i] * (i - mean) * (i - mean);
    }
    standard_deviation = sqrt(standard_deviation / nb_positions_attributed);
    std::cout << std::endl
              << "Et la moyenne vaut : " << mean << " (théoriquement " << 3
              << ")" << std::endl;
    std::cout << "Et l'écart type vaut : " << standard_deviation
              << " (théoriquement " << sqrt(6 * 6 / 12.) << ")" << std::endl;
  } else {
    // gaussian should be here... have to change
    for (int i = 0; i < nb_positions; i++) {
      draw_line(i, gaussian_probabilities[i] * 45);
      mean += i * positions[i];
      nb_positions_attributed += positions[i];
    }
    mean /= nb_positions_attributed;
    for (int i = 0; i < nb_positions; i++) {
      standard_deviation += positions[i] * (i - mean) * (i - mean);
    }
    standard_deviation = sqrt(standard_deviation / nb_positions_attributed);
    std::cout << std::endl
              << "Et la moyenne vaut : " << mean << " (théoriquement " << 2.5
              << ")" << std::endl;
    std::cout << "Et l'écart type vaut : " << standard_deviation
              << " (théoriquement " << 1.5 << ")" << std::endl;
  }
  std::cout << std::endl;
}

void statistic(float p, float alpha, float lambda, int difficulty,
               std::vector<float> gaussian_probabilities) {
  display_exp(stats.exp, lambda);
  display_uniform_position(stats.positions, stats.nb_objects, stats.rounds,
                           difficulty, gaussian_probabilities);
  reload();
}