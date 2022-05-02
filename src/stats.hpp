#include <vector>
#include <iostream>

struct Statistics {
  std::vector<int> positions;
  int bernoulli = 0;
  int rademacher = 0;
  int nb_objects = 0;
  std::vector<float> exp;
  int rounds = 0;
  Statistics() : positions(7,0){};
};

void statistic(Statistics stats, float p, float alpha, float lambda, int difficulty, std::vector<float> gaussian_probabilities);