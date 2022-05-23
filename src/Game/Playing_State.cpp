#include "../gaming.hpp"
#include "Game.hpp"

void Playing_State::handleInput(Game &game, const Input &input,
                                p6::Context &ctx) {
  if (input.key.logical == "q") {
    game.change_state(&Game::menu);
  }
  on_click(ctx.mouse());
}

void Playing_State::update(Game &game, p6::Context &ctx) {
  if ((this->start_time + this->time_game - ctx.time()) > 0.0000001f) {
    play_game(ctx, this->start_time);
  } else {
    end_game();
    game.change_state(&Game::menu);
  }
  ctx.mouse_pressed = [&](p6::MouseButton mouse) {
    Input input(mouse);
    this->handleInput(game, input, ctx);
  };

  ctx.key_pressed = [&](p6::Key key) {
    Input input(key);
    this->handleInput(game, input, ctx);
  };
}