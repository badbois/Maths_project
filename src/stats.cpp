#include "stats.hpp"
#include "math.h"
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

void display_exp(std::vector<float> exp, float lambda){
  float mean = 0;
  for (int i = 0; i<exp.size(); i++){
    mean+=exp[i];
  }
  mean/=exp.size();
  float standard_deviation = 0;
  for (int i = 0; i<exp.size(); i++){
    standard_deviation+=(exp[i]-mean)*(exp[i]-mean);
  }
  standard_deviation = sqrt(standard_deviation/exp.size());

  std::cout << "La moyenne de temps avant le prochain combo est : " << mean << std::endl;
  std::cout << "Théoriquement, cette moyenne était de : " << lambda << std::endl;

  std::cout << "L'écart type associé est : " << standard_deviation << std::endl;
  std::cout << "Théoriquement, cet écart type était de : " << lambda << std::endl;

  std::cout << std::endl;
}

void display_uniform_position(std::vector<int> positions, int nb_objects, int rounds, int difficulty, std::vector<float> gaussian_probabilities) {
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
      draw_line(i, gaussian_probabilities[i]*50);
    }
  }
  std::cout << std::endl;
}

void statistic(Statistics stats, float p, float alpha, float lambda, int difficulty, std::vector<float> gaussian_probabilities) {
  //pas sure que ce soit très pertinent.. puis en plus faudrait compter autrement puisque c'est pas indépendant
  //display_rotation_mean(stats.bernoulli, p, stats.nb_objects);
  //display_rotation_direction_mean(stats.rademacher, 4);
  display_exp(stats.exp, lambda);
  display_uniform_position(stats.positions, stats.nb_objects, stats.rounds, difficulty, gaussian_probabilities);
}