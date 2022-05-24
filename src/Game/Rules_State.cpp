#include "Game.hpp"

void display_rules(p6::Context &ctx) {
  ctx.background({0.f, 0.f, 0.f});
  ctx.fill = {1., 1., 1., 1};
  ctx.text_size = 0.025f;
  ctx.text(u"Click on the", p6::Center{0.f, 0.4f});
  ctx.text(u"single unique shape ", p6::Center{0.f, 0.3f});
  ctx.text(u"to earn points. If you suceed", p6::Center{0.f, 0.2f});
  ctx.text(u"you gain some combo multiplicator,", p6::Center{0.f, 0.1f});
  ctx.text(u"if it's fast enougth", p6::Center{0.f, 0.0f});
  ctx.text(u"you gain more combo", p6::Center{0.f, -0.1f});
  ctx.text(u"if you fail, the combo multiplicator ", p6::Center{0.f, -0.2f});
  ctx.text(u"is reset. You have a minute.", p6::Center{0.f, -0.3f});

  ctx.text_size = 0.02f;
  ctx.text(u"retour:M", p6::Center{0.8f, 0.9f});
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
