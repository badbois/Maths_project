#include "draw.hpp"
#include <math.h>

void draw_object(p6::Context &ctx, const Object &object,
                 const p6::Angle rotation, float pas) {
  float i = -1. + (object.get_position().y + 1.) * pas;
  float j = -1. + (object.get_position().x + 1.) * pas;
  ctx.fill = object.get_color();
  switch (object.get_shape()) {
  case Shape::SQUARE:
    ctx.square(p6::Center{i, j}, p6::Radius{0.05f},
               p6::Rotation{rotation * object.get_Rotation()});
    break;
  case Shape::CIRCLE:
    ctx.circle(p6::Center{i, j}, p6::Radius{0.05f});
    break;
  case Shape::TRIANGLE:
    float cosinus =
        cos((rotation * object.get_Rotation()).as_radians());
    float sinus =
        sin((rotation * object.get_Rotation()).as_radians());

    ctx.triangle({cosinus * 0.05f - sinus * (-0.05f) + i,
                  sinus * 0.05f + cosinus * (-0.05f) + j},
                 {cosinus * (-0.05f) - sinus * (-0.05f) + i,
                  sinus * (-0.05f) + cosinus * (-0.05f) + j},
                 {-sinus * 0.05f + i, +cosinus * 0.05f + j});

    break;
  }
}

void draw_grid_of_objects(p6::Context &ctx, const std::vector<Object> &objects,
                          const p6::Angle rotation, float pas) {
  int i = 0;
  for (auto &object : objects) {
    draw_object(ctx, object, rotation, pas);
    i++;
  }
}