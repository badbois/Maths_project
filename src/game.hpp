#include <p6/p6.h>


struct GameState {
  int combo {1};
  float click_time {0};
  int score{0};
  int latest_shape{0};
};

void set_game_grid();

void play_game(p6::Context &ctx, bool &is_playing, float game_start_time);