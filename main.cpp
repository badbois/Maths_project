#include <iostream>
#include <p6/p6.h>

int main() {
  auto ctx = p6::Context{{720, 720, "My p6 project"}};
  float pas = 1 / 4.0;
  p6::Angle rotation = 0.011_turn;
  float time = 0;
  ctx.use_stroke = false;
  ctx.update = [&]() {
    ctx.background({0.2f, 0.1f, 0.3f});
    for (float i = -1 + pas; i < 1; i += pas) {
      for (float j = -1 + pas; j < 1; j += pas) {
        ctx.square(p6::Center{i, j}, p6::Radius{0.05f}, p6::Rotation{rotation});
      }
    };
    time = ctx.time();
    rotation = time * 0.1_turn;
    ctx.circle(p6::Center{ctx.mouse()}, p6::Radius{0.03f});

    ctx.mouse_pressed = [](p6::MouseButton) { std::cout << "Hello World\n"; };
  };
  ctx.start();
}