#include "stats.hpp"
#include <iostream>

void display_rotation_mean(float mean, float p, int n) {
  std::cout << "Moyenne de rotation: " << mean << std::endl;
  std::cout << "(Moyenne de rotation théorique : " << n * p << ")" << std::endl;
  std::cout << std::endl;
}

void display_rotation_direction_mean(float mean, float theorical_mean) {
  std::cout << "Moyenne de sens de rotation: " << mean << std::endl;
  std::cout << "(Moyenne de sens de rotation théorique : " << theorical_mean
            << ")" << std::endl;
  std::cout << std::endl;
}

void draw_line(int nb_line, int nb) {
  std::cout << nb_line << " : ";
  for (int i = 0; i < nb; i++) {
    std::cout << "*";
  }
  std::cout << std::endl;
}

void display_uniform_position(std::vector<int> positions, int nb_objects, int rounds, int difficulty) {
  int nb_positions = positions.size();
  std::cout << "Diagramme des positions (x et y confondus) :" << std::endl;
  for (int i = 0; i < nb_positions; i++) {
    draw_line(
        i,
        static_cast<int>(positions[i]/(rounds+1))); 
  }
  std::cout << std::endl;
  std::cout << "Diagramme des positions théorique :" << std::endl;
  if (difficulty == 1) {
    for (int i = 0; i < nb_positions; i++) {
      draw_line(i, 2*nb_objects/(nb_positions*(rounds+1)));
    }
  } else {
    // gaussian should be here... have to change
    for (int i = 0; i < nb_positions; i++) {
      draw_line(i, 5);
    }
  }
  std::cout << std::endl;
}

void statistic(Statistics stats, float p, float alpha, int difficulty) {
  display_rotation_mean(stats.bernoulli, p, stats.nb_objects);
  display_rotation_direction_mean(stats.rademacher, 4);
  display_uniform_position(stats.positions, stats.nb_objects, stats.rounds, difficulty);
}