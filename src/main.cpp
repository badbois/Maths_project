#include <iostream>
#include <p6/p6.h>

#include <vector>

#include "Game/Game.hpp"

Playing_State Game::playing;
Menu_State Game::menu;
Scoreboard_State Game::scoreboard;
Rules_State Game::rules;
End_State Game::end;

int main() {
  Game game;
  game.change_state(&Game::menu);
  try {
    auto ctx = p6::Context{{720, 720, "Unique project"}};
    ctx.time_perceived_as_realtime();
    ctx.use_stroke = false;

    // Main loop
    ctx.update = [&]() {
      ctx.background({0.f, 0.f, 0.f});
      ctx.fill = {1., 1., 1., 1};
      game.update(ctx);
    };
    ctx.start();
  }
  // Log any error that might occur
  catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
  }
}