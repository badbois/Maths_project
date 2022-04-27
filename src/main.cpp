#include <iostream>
#include <p6/p6.h>

#include <vector>

#include "Object.hpp"
#include "draw.hpp"
#include "game.hpp"

void show_menu(p6::Context &ctx, bool &is_playing, float &game_start_time) {
  ctx.text(u"Prout le pet", p6::Center{0.f, 0.f});
  ctx.key_pressed = [&](p6::Key key) {
    std::cout << key.logical << std::endl;
    if (key.logical == "q") {
      ctx.stop();
    } else if (key.logical == "p") {
      is_playing = true;
      game_start_time = ctx.time();
    }
  };
}

int main() {
  try {
    auto ctx = p6::Context{{720, 720, "My p6 project"}};
    ctx.time_perceived_as_realtime();
    float game_start_time = 0;

    ctx.use_stroke = false;
    bool is_playing = false;
    set_game_grid();

    // Main loop
    ctx.update = [&]() {
      ctx.background({0.2f, 0.1f, 0.3f});
      ctx.fill = {1., 1., 1., 0.5};
      if (is_playing) {
        play_game(ctx, is_playing, game_start_time);
      } else {
        show_menu(ctx, is_playing, game_start_time);
      }
    };
    ctx.start();
  }
  // Log any error that might occur
  catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
  }
}