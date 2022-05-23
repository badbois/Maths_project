#include <p6/p6.h>

class Game;

struct Input {
  p6::Key key;
  p6::MouseButton mouse;
  int state; // 0 for key, 1 for mouse
  Input(p6::Key new_key) : key(new_key), mouse(), state(0){};
  Input(p6::MouseButton new_mouse) : mouse(new_mouse), key(), state(1) {}
};

class Game_State {
public:
  virtual ~Game_State() {}
  virtual void handleInput(Game &game, const Input &input, p6::Context &ctx) {}
  virtual void update(Game &game, p6::Context &ctx) {}
};

class Playing_State : public Game_State {
public:
  Playing_State() : start_time(0) {}

  virtual void handleInput(Game &game, const Input &input, p6::Context &ctx);

  virtual void update(Game &game, p6::Context &ctx);

  void set_time(float time) { start_time = time; };

private:
  float start_time;
  float time_game = 60;
};

class Menu_State : public Game_State {
public:
  Menu_State() {}

  virtual void handleInput(Game &game, const Input &input, p6::Context &ctx);

  virtual void update(Game &game, p6::Context &ctx);
};

class Scoreboard_State : public Game_State {
public:
  Scoreboard_State() {}

  virtual void handleInput(Game &game, const Input &input, p6::Context &ctx);
  virtual void update(Game &game, p6::Context &ctx);
};

class End_State : public Game_State {
public:
  End_State() {}

  virtual void handleInput(Game &game, const Input &input, p6::Context &ctx);
  virtual void update(Game &game, p6::Context &ctx);

private:
  //
};

class Game {
public:
  ~Game() {}
  static Playing_State playing;
  static Menu_State menu;
  static Scoreboard_State scoreboard;
  static End_State end;
  virtual void handleInput(const Input &input, p6::Context &ctx) {
    state_->handleInput(*this, input, ctx);
  }

  virtual void update(p6::Context &ctx) { state_->update(*this, ctx); }
  virtual void change_state(Game_State *state) { state_ = state; };

private:
  Game_State *state_;
};