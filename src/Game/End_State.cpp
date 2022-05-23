#include "../gaming.hpp"
#include "Game.hpp"

void End_State::handleInput(Game &game, const Input &input, p6::Context &ctx) {
  if (input.key.logical == "m") {
    game.change_state(&Game::menu);
  } else if (input.key.logical == "s") {
    game.change_state(&Game::scoreboard);
  } else if (input.key.logical == "q") {
    ctx.stop();
  }
};

void End_State::update(Game &game, p6::Context &ctx) {
  show_end_game(ctx);
  ctx.key_pressed = [&](p6::Key key) {
    Input input(key);
    this->handleInput(game, input, ctx);
  };
}