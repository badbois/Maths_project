#include <iostream>
#include <p6/p6.h>

#include <vector>

#include "Object.hpp"
#include "Rand.hpp"
#include "include/random.hpp"

int nb_objects_by_line = 7;

enum class Color {
  RED,
  BLUE,
  YELLOW,
  count = 3,
};

enum class Rotation {
  NONE,
  LEFT,
  RIGHT,
  count = 3,
};

enum class Size {
  LITTLE,
  MEDIUM,
  LARGE,
  count = 3,
};

enum class Shape {
  CIRCLE,
  SQUARE,
  TRIANGLE,
  count = 3,
};

struct Position2D {
  int x;
  int y;
  Position2D(int PosX, int PosY) : x(PosX), y(PosY) {}
};

struct Object {
  Shape shape;
  Color color;
  Rotation rotation;
  Size size;
  Position2D position;
  Object(Shape _shape, Color _color, Rotation _rotation, Size _size,
         Position2D _pos)
      : shape(_shape), color(_color), rotation(_rotation), size(_size),
        position(_pos){};

  Object()
      : shape(
            static_cast<Shape>(randomUniform(static_cast<int>(Shape::count)))),
        color(
            static_cast<Color>(randomUniform(static_cast<int>(Color::count)))),
        rotation(static_cast<Rotation>(
            randomUniform(static_cast<int>(Rotation::count)))),
        size(static_cast<Size>(randomUniform(static_cast<int>(Size::count)))),
        position(Position2D(randomUniform(nb_objects_by_line),
                            randomUniform(nb_objects_by_line))){};
};

void drawObject(p6::Context &ctx, Position2D position, p6::Angle rotation,
                Shape shape, float pas) {
  float i = -1. + (position.y + 1.) * pas;
  float j = -1. + (position.x + 1.) * pas;
  switch (shape) {
  case Shape::SQUARE:
    ctx.square(p6::Center{i, j}, p6::Radius{0.05f}, p6::Rotation{rotation});
    break;
  case Shape::CIRCLE:
    ctx.circle(p6::Center{i, j}, p6::Radius{0.05f});
    break;
  }
}

void drawColor(p6::Context &ctx, Color color) {
  switch (color) {
  case Color::RED:
    ctx.fill = {1., 0., 0.};
    break;
  case Color::BLUE:
    ctx.fill = {0., 0., 1.};
    break;
  case Color::YELLOW:
    ctx.fill = {1., 1., 0.};
    break;
  }
}


void play_game(p6::Context &ctx, const std::vector<Object> &objects, p6::Angle rotation, float pas, float time, bool &is_playing, float game_start_time) {
  if((game_start_time+10) - ctx.time() > 0.0000001f){
    for (auto &object : objects) {
      drawColor(ctx, object.color);
      drawObject(ctx, object.position, rotation, object.shape, pas);
    }
    time = ctx.time();
    rotation = time * 0.1_turn;
    ctx.circle(p6::Center{ctx.mouse()}, p6::Radius{0.03f});

    ctx.mouse_pressed = [](p6::MouseButton) {
      std::cout << "time combo " << timeUntilCombo(5.) << std::endl;
    };
  }else{
    is_playing = false;
  }
}


void show_menu(p6::Context &ctx, bool &is_playing, float &game_start_time) {
  ctx.key_pressed = [&](p6::Key key) {
    std::cout << key.logical << std::endl;
    if(key.logical == "q") {
      ctx.stop();
    }
    else if(key.logical == "p") {
      is_playing = true;
      game_start_time = ctx.time();
    }
  };
   
}


int main() {
  try{
    auto ctx = p6::Context{{720, 720, "My p6 project"}};
    ctx.set_time_mode_realtime();
    //Preparation of the game
    float pas = 2. / (nb_objects_by_line + 1);
    p6::Angle rotation = 0.011_turn;
    float time = 0;
    float game_start_time = 0;
    std::vector<Object> objects(20);
    ctx.use_stroke = false;
    bool is_playing = false;
    


    //Main loop
    ctx.update = [&]() {
    ctx.background({0.2f, 0.1f, 0.3f});
    ctx.fill = {1., 1., 1., 0.5};
    if(is_playing) {
      play_game(ctx, objects, rotation, pas, time, is_playing, game_start_time);
    }else{
      show_menu(ctx, is_playing, game_start_time);
    } 
    };
    ctx.start();
  }
  // Log any error that might occur
    catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
}