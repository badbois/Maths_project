#include "Game.hpp"

void display_rules(p6::Context &ctx) {
  ctx.background({0.f, 0.f, 0.f});
  ctx.fill = {1., 1., 1., 1};
  ctx.text_size = 0.03f;
  ctx.text(u"Click on the single unique", p6::Center{0.f, 0.5f});
  ctx.text(u"shape to earn points.", p6::Center{0.f, 0.4f});
  ctx.text(u"If you suceed you gain", p6::Center{0.f, 0.2f});
  ctx.text(u"some combo multiplicator", p6::Center{0.f, 0.1f});
  ctx.text(u"If it's fast enough", p6::Center{0.f, 0.0f});
  ctx.text(u"you gain more combo,", p6::Center{0.f, -0.1f});
  ctx.text(u"if you fail,", p6::Center{0.f, -0.2f});
  ctx.text(u"the combo multiplicator", p6::Center{0.f, -0.3f});
  ctx.text(u"is reset", p6::Center{0.f, -0.4f});
  ctx.fill = {1., 0., 0., 1};
  ctx.text_size = 0.04f;
  ctx.text(u"You have a minute ", p6::Center{0.f, -0.6f});
  ctx.fill = {1., 1., 1., 1};
  ctx.text_size = 0.02f;
  ctx.text(u"menu:M", p6::Center{0.8f, 0.9f});
}

void Rules_State::handleInput(Game &game, const Input &input,
                              p6::Context &ctx) {
  if (input.key.logical == "m") {
    game.change_state(&Game::menu);
  }
};

void Rules_State::update(Game &game, p6::Context &ctx) {
  display_rules(ctx);
  ctx.key_pressed = [&](p6::Key key) {
    Input input(key);
    this->handleInput(game, input, ctx);
  };
};
