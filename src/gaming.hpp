#include <p6/p6.h>

struct Game_Infos {
  int combo{1};
  float click_time{0};
  int score{0};
  int latest_shape{0};
  bool victory = false;
  int combo_change = 0;
};

void set_game_grid();

void play_game(p6::Context &ctx, float game_start_time);
void end_game();
void on_click(glm::vec2 mouse_position);
void show_end_game(p6::Context &ctx);
void reset_game_infos();

void show_combo(p6::Context &ctx);