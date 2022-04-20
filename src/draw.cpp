#include "draw.hpp"

void draw_object(p6::Context &ctx, const Object &object,
                 const p6::Angle rotation, float pas) {
  float i = -1. + (object.get_position().y + 1.) * pas;
  float j = -1. + (object.get_position().x + 1.) * pas;
  ctx.fill = object.get_color();
  switch (object.get_shape()) {
  case Shape::SQUARE:
    ctx.square(p6::Center{i, j}, p6::Radius{0.05f},
               p6::Rotation{object.get_rotating_direction() * rotation});
    break;
  case Shape::CIRCLE:
    ctx.circle(p6::Center{i, j}, p6::Radius{0.05f});
    break;
  case Shape::TRIANGLE:
    ctx.triangle({i+0.05f, j-0.05f}, {i-0.05f, j-0.05f}, {i, j+0.05f});
    break;
  }
}

void draw_grid_of_objects(p6::Context &ctx, const std::vector<Object> &objects,
                          const p6::Angle rotation, float pas) {
  for (auto &object : objects) {
    draw_object(ctx, object, rotation, pas);
  }
}