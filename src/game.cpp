#include <iostream>

#include "draw.hpp"
#include "game.hpp"
#include "rand.hpp"

int nb_objects_by_line = 7;
int nb_first_objects = 8;
float pas = 2. / (nb_objects_by_line + 1);
std::vector<p6::Color> colors = {{1., 0., 0.},   {0., 1., 0.}, {0., 0., 1.},
                                 {1., 1., 0.},   {1., 0., 1.}, {0., 1., 1.},
                                 {0.5, 0.5, 0.5}};
std::vector<Object> objects;

GameState game_state;

void adding_different_objects(std::vector<Object> &different_objects) {
  int unique_color = different_objects[0].get_color_index();
  for (int i = 0; i < nb_first_objects; i++) {
    Object tmp(colors, nb_objects_by_line);
    tmp.set_color_difficult(unique_color, colors);
    if (std::find(different_objects.begin(), different_objects.end(), tmp) ==
        different_objects.end()) {
      different_objects.push_back(tmp);
    };
  };
};

void create_objects() {
  std::vector<Object> different_objects;
  Object unique_object(colors, nb_objects_by_line, game_state.latest_shape);
  different_objects.push_back(unique_object);
  objects.clear();
  objects.push_back(unique_object);
  adding_different_objects(different_objects);
  for (int i = 1; i < different_objects.size(); i++) {
    for (int j = 2; j < 5; j++) {
      objects.push_back(different_objects[i]);
    }
  }
};

void set_game_grid() {
  create_objects();
  std::vector<Position2D> positions = create_positions(objects, 7);
  set_all_positions(objects, positions);
}

Position2D from_position_to_case(glm::vec2 position) {
  Position2D case_position;
  case_position.x = (position.y + 1) / pas - 1 + pas / 2;
  case_position.y = (position.x + 1) / pas - 1 + pas / 2;
  return case_position;
}

void on_click(glm::vec2 mouse_position) {
  if (from_position_to_case(mouse_position) == objects[0].get_position()) {
    if (game_state.click_time < time_until_combo(1.)) {
      std::cout << "le tps : " << game_state.click_time << std::endl;
      game_state.combo++;
    }
    game_state.score += game_state.combo * 10;
    if (game_state.combo < 7) {
      game_state.combo++;
    };
  } else {
    game_state.combo = 1;
  };
  std::cout << "combot : " << game_state.combo << std::endl;
  std::cout << "Le score vaut : " << game_state.score << std::endl;
  set_game_grid();
  game_state.latest_shape = static_cast<int>(objects[0].get_shape());
  game_state.click_time = 0;
}

void play_game(p6::Context &ctx, bool &is_playing, float game_start_time) {
  set_difficulty(1);
 // if ((game_start_time + 10) - ctx.time() > 0.0000001f) {
    draw_grid_of_objects(ctx, objects, ctx.time() * 0.1_turn, pas);
    ctx.fill = {1., 1., 1., 0.8};
    ctx.circle(p6::Center{ctx.mouse()}, p6::Radius{0.03f});
    game_state.click_time += 0.01;

    ctx.mouse_pressed = [&ctx](p6::MouseButton) { on_click(ctx.mouse()); };
  // } else {
  //   is_playing = false;
  // }
}