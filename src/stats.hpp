#include <vector>

void update_stats(int posx, int posy, int rotation);
void add_round_stats();
void add_exp_stats(float rand);
void statistic(float p, float lambda,
               int difficulty, std::vector<float> gaussian_probabilities);