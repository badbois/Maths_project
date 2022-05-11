#pragma once
#include <vector>

// to set the parameters
void set_difficulty(const int difficulty_gamer);
void set_gaussian_probabilities();

// random function called to set objects
float random_rotation();
int random_shape(const int nb_of_shapes);
int markov(int latest_shape);
int random_color(const int nb_of_colors, const int unique_color);
int random_color(const int nb_of_colors);
int random_position(const int nb_of_objects_by_line);

// called for combo
float time_until_combo();

// statistics
void display_statistics();
void update_stats(int posx, int posy, int rotation);
void add_round_stats();