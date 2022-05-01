#include <vector>
#include <iostream>

struct Statistics {
  std::vector<int> positions;
  int bernoulli = 0;
  int rademacher = 0;
  int nb_objects = 0;
  int rounds = 0;
  Statistics() : positions(7,0){};
};

void statistic(Statistics stats, float p, float alpha, int difficulty);