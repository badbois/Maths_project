#pragma once

void set_difficulty(const int difficulty_gamer);
int random_uniform(const int nb_values);
float time_until_combo(const float average_comboTime);
int random_rotation_direction();
int random_shape(const int nb_of_shapes);
int markov(int latest_shape);
int random_color(const int nb_of_colors, const int unique_color=0);
int random_position(const int nb_of_objects_by_line);