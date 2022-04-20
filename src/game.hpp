#include <p6/p6.h>
#include <vector>

struct GameState {
  int combo;
  float click_time;
  int score;
};

void initialize_game();

void play_game(p6::Context &ctx, bool &is_playing, float game_start_time);