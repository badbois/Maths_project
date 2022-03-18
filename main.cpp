#include <p6/p6.h>

int main() {
  auto ctx = p6::Context{};
  p6::Angle rotation = 0.011_turn;
  ctx.mouse_scrolled = [&](p6::MouseScroll e) { rotation += e.dy * 0.01_turn; };
  ctx.update = [&]() {
    ctx.background({});
    ctx.stroke = {1, 1, 1, 1};
    // White square positioned by Center
    ctx.square(p6::Center{ctx.mouse()}, p6::Radius{0.3f},
               p6::Rotation{rotation});
    // Red square positioned by Top Left Corner
    ctx.fill = {1, 0, 0, 0.5};
    ctx.square(p6::TopLeftCorner{ctx.mouse()}, p6::Radius{0.3f},
               p6::Rotation{rotation});
    // Green square positioned by Top Right Corner
    ctx.fill = {0, 1, 0, 0.5};
    ctx.square(p6::TopRightCorner{ctx.mouse()}, p6::Radius{0.3f},
               p6::Rotation{rotation});
    // Blue square positioned by Bottom Left Corner
    ctx.fill = {0, 0, 1, 0.5};
    ctx.square(p6::BottomLeftCorner{ctx.mouse()}, p6::Radius{0.3f},
               p6::Rotation{rotation});
    // Cyan square positioned by Bottom Right Corner
    ctx.fill = {0, 1, 1, 0.5};
    ctx.square(p6::BottomRightCorner{ctx.mouse()}, p6::Radius{0.3f},
               p6::Rotation{rotation});
  };
  ctx.start();
}