#include "../gaming.hpp"
#include "Game.hpp"

void Playing_State::handleInput(Game &game, const Input &input,
                                p6::Context &ctx) {
  if (input.state == 0 && input.key.logical == "m") {
    reset_game_infos();
    game.change_state(&Game::menu);
  } else if (input.state == 1) {
    on_click(ctx.mouse());
  }
}

void Playing_State::update(Game &game, p6::Context &ctx) {
  if ((this->start_time + this->time_game - ctx.time()) > 0.0000001f) {
    play_game(ctx, this->start_time);
  } else {
    end_game();
    game.change_state(&Game::end);
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