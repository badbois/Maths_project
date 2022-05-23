#include "../score.hpp"
#include "Game.hpp"

void Scoreboard_State::handleInput(Game &game, const Input &input,
                                   p6::Context &ctx) {
  if (input.key.logical == "m") {
    game.change_state(&Game::menu);
  }
};

void Scoreboard_State::update(Game &game, p6::Context &ctx) {
  display_scoreboard(ctx);
  ctx.key_pressed = [&](p6::Key key) {
    Input input(key);
    this->handleInput(game, input, ctx);
  };
};