#include <iostream>

#include "draw.hpp"
#include "game.hpp"
#include "rand.hpp"
#include "score.hpp"
#include <string>

int nb_objects_by_line = 7;
int nb_first_objects = 8;
float pas = 2. / (nb_objects_by_line + 1);
std::vector<p6::Color> colors = {{1., 0., 0.},   {0., 1., 0.}, {0., 0., 1.},
                                 {1., 1., 0.},   {1., 0., 1.}, {0., 1., 1.},
                                 {0.5, 0.5, 0.5}};
std::vector<Object> objects;

GameState game_state;

// fill different_objects with different objects
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

// Create and fill the objects vector with unique objects at the first place
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

// set the grid of the game
void set_game_grid() {
  create_objects();
  std::vector<Position2D> positions = create_positions(objects, 7);
  set_all_positions(objects, positions);
}

// Convert P6 position to our grid coordinates position
Position2D from_position_to_case(glm::vec2 position) {
  Position2D case_position;
  case_position.x = (position.y + 1) / pas - 1 + pas / 2;
  case_position.y = (position.x + 1) / pas - 1 + pas / 2;
  return case_position;
}

// Check if we clicked on the good object and give us point if we did
void on_click(glm::vec2 mouse_position) {
  add_round_stats();
  //not sure if the statistics should be on the time in general, or only when we clicked right ?
  float time_combo = time_until_combo();
  if (from_position_to_case(mouse_position) == objects[0].get_position()) {
    if (game_state.click_time < time_combo) {
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
  // std::cout << "combot : " << game_state.combo << std::endl;
  // std::cout << "Le score vaut : " << game_state.score << std::endl;
  set_game_grid();
  game_state.latest_shape = static_cast<int>(objects[0].get_shape());
  game_state.click_time = 0;
}

// Reset the game state after the end of the game
void reset_game_state() {
  game_state.score = 0;
  game_state.combo = 1;
  game_state.click_time = 0;
  game_state.latest_shape = 0;
}

// Display the lefting time in the top right corner
void show_time_left(p6::Context &ctx, float game_start_time) {
  ctx.fill = {1., 1., 1., 1};
  ctx.text_size = 0.02f;
  int time_left = static_cast<int>((game_start_time + 60) - ctx.time());
  std::string time_left_string = std::to_string(time_left);
  std::u16string time_left_u16string =
      std::u16string(time_left_string.begin(), time_left_string.end());
  ctx.text(time_left_u16string, p6::Center{0.9f, 0.9f});
}

// Display the score and the combo in the top
void show_score_and_combo(p6::Context &ctx, int score, int combo) {
  ctx.fill = {1., 1., 1., 1};
  ctx.text_size = 0.02f;
  // convert int to u16string
  std::string score_string = std::to_string(score);
  std::u16string score_u16string =
      std::u16string(score_string.begin(), score_string.end());

  std::string combo_string = std::to_string(combo);
  std::u16string combo_u16string =
      std::u16string(combo_string.begin(), combo_string.end());

  ctx.text(u"score:" + score_u16string + u"  combo:x" + combo_u16string,
           p6::Center{0.f, 0.9f});
}

void play_game(p6::Context &ctx, bool &is_playing, float game_start_time) {
  set_difficulty(0);
  if ((game_start_time + 10) - ctx.time() > 0.0000001f) {
    draw_grid_of_objects(ctx, objects, ctx.time() * 0.1_turn, pas);
    ctx.fill = {1., 1., 1., 0.8};
    ctx.circle(p6::Center{ctx.mouse()}, p6::Radius{0.03f});
    game_state.click_time += 0.01;

    show_score_and_combo(ctx, game_state.score, game_state.combo);
    show_time_left(ctx, game_start_time);

    ctx.mouse_pressed = [&ctx](p6::MouseButton) { on_click(ctx.mouse()); };
  } else {
    add_new_score(game_state.score);
    reset_game_state();
    is_playing = false;
    display_statistics();
    set_game_grid();
  }
}
