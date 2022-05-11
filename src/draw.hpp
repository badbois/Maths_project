#pragma once

#include "Object.hpp"

void draw_grid_of_objects(p6::Context &ctx, const std::vector<Object> &objects,
                          const p6::Angle rotation, float pas);