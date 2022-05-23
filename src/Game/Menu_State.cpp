#include "../rand.hpp"
#include "Game.hpp"

void Menu_State::handleInput(Game &game, const Input &input, p6::Context &ctx) {
  if (input.key.logical == "q") {
    ctx.stop();
  } else if (input.key.logical == "e") {
    game.playing.set_time(ctx.time());
    set_difficulty(0);
    set_gaussian_probabilities();
    game.change_state(&Game::playing);
  } else if (input.key.logical == "d") {
    set_difficulty(1);
    game.playing.set_time(ctx.time());
    set_gaussian_probabilities();
    game.change_state(&Game::playing);
  } else if (input.key.logical == "s") {
    game.change_state(&Game::scoreboard);
  }
}

void Menu_State::update(Game &game, p6::Context &ctx) {
  ctx.text_size = 0.05f;
  ctx.text(u"New game:", p6::Center{-0.3f, 0.6f});
  ctx.text_size = 0.03f;
  ctx.text(u"Easy:E", p6::TopLeftCorner{0.2f, 0.65f});
  ctx.text(u"Difficult:D", p6::TopLeftCorner{0.2f, 0.55});
  ctx.text_size = 0.05f;
  ctx.text(u"Scoreboard:S", p6::Center{0.f, 0.2f});
  ctx.text(u"Rules:R", p6::Center{0.f, -0.2f});
  ctx.text(u"Quit:Q", p6::Center{0.f, -0.6f});

  ctx.key_pressed = [&](p6::Key key) {
    Input input(key);
    this->handleInput(game, input, ctx);
  };
}