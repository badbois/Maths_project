#pragma once
#include <vector>

void set_difficulty(const int difficulty_gamer);
void set_gaussian_probabilities();
int random_uniform(const int nb_values);
float time_until_combo();
void display_statistics();
int random_rotation_direction();
int random_shape(const int nb_of_shapes);
int markov(int latest_shape);
int random_color(const int nb_of_colors, const int unique_color);
int random_color(const int nb_of_colors);
int random_position(const int nb_of_objects_by_line);
void update_stats(int posx, int posy, int rotation);
void add_round_stats();