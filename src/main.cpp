#include <iostream>
#include <p6/p6.h>

#include <vector>

#include "Object.hpp"
#include "draw.hpp"
#include "gaming.hpp"
#include "score.hpp"

#include "Game/Game.hpp"

Playing_State Game::playing;
Menu_State Game::menu;
Scoreboard_State Game::scoreboard;

void show_menu(p6::Context &ctx, bool &is_playing, bool &is_scoreboard,
               float &game_start_time) {
  ctx.text_size = 0.05f;
  ctx.text(u"New game:P", p6::Center{0.f, 0.6f});
  ctx.text(u"Scoreboard:S", p6::Center{0.f, 0.2f});
  ctx.text(u"Rules:R", p6::Center{0.f, -0.2f});
  ctx.text(u"Quit:Q", p6::Center{0.f, -0.6f});

  ctx.key_pressed = [&](p6::Key key) {
    std::cout << key.logical << std::endl;
    if (key.logical == "q") {
      ctx.stop();
    } else if (key.logical == "p") {
      if (!is_playing && !is_scoreboard) {
        is_playing = true;
        game_start_time = ctx.time();
      }
    } else if (key.logical == "s") {
      if (!is_playing) {
        is_scoreboard = true;
      }
    }
    if (is_scoreboard) {
      if (key.logical == "m") {
        is_scoreboard = false;
      }
    }
  };
};

int main() {
  Game game;
  game.change_state(&Game::menu);
  try {
    auto ctx = p6::Context{{720, 720, "Unique project"}};
    ctx.time_perceived_as_realtime();
    float game_start_time = 0;

    ctx.use_stroke = false;
    bool is_playing = false;
    bool is_scoreboard = false;
    set_gaussian_probabilities();
    set_game_grid();

    // Main loop
    ctx.update = [&]() {
      ctx.background({0.f, 0.f, 0.f});
      ctx.fill = {1., 1., 1., 1};
      game.update(ctx);
      // if (is_playing && !is_scoreboard) {
      //   play_game(ctx, is_playing, game_start_time);
      // } else if (!is_playing && !is_scoreboard) {
      //   show_menu(ctx, is_playing, is_scoreboard, game_start_time);
      // } else if (is_scoreboard) {
      //   display_scoreboard(ctx);
      // }
    };
    ctx.start();
  }
  // Log any error that might occur
  catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
  }
}