#pragma once

#include "Object.hpp"

void draw_object(p6::Context &ctx, const Object &object, const p6::Angle rotation,
                 float pas);

void draw_grid_of_objects(p6::Context &ctx, const std::vector<Object> &objects,
                          const p6::Angle rotation, float pas);