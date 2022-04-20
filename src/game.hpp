#include <p6/p6.h>
#include <vector>

struct GameState {
  int combo;
  float click_time;
  int score;
  GameState() : combo(1), click_time(0), score(0) {}
};

void set_game_grid();

void play_game(p6::Context &ctx, bool &is_playing, float game_start_time);