#pragma once

#include "rand.hpp"
#include <iostream>
#include <p6/p6.h>
#include <vector>

struct Rotating_direction {
  int direction; // sens de rotation
  Rotating_direction() : direction(0) {}
  explicit Rotating_direction(int _direction) : direction(_direction){};
  bool operator==(const Rotating_direction &other) const {
    return direction == other.direction;
  };
  bool operator==(const int other) const { return direction == other; }
};

enum class Shape {
  CIRCLE,
  SQUARE,
  TRIANGLE,
  count,
};

struct Position2D {
  int x;
  int y;
  Position2D() : x(0), y(0) {}
  Position2D(int PosX, int PosY) : x(PosX), y(PosY) {}
  bool operator==(const Position2D &other) const {
    return x == other.x && y == other.y;
  }
};

bool compare_colors(const p6::Color &color1, const p6::Color &color2);

class Object {
private:
  Shape shape;
  p6::Color color;
  Rotating_direction rotating_direction;
  Position2D position;

public:
  // Default constructor
  Object()
      : shape(Shape::CIRCLE), color(p6::Color(1.f, 0.f, 0.f)),
        rotating_direction(Rotating_direction()), position(Position2D(0, 0)){};

  // Constructor
  explicit Object(const std::vector<p6::Color> &colors,
                  const int nb_objects_by_line)
      : shape(static_cast<Shape>(random_shape(static_cast<int>(Shape::count)))),
        color(colors[random_color(colors.size())]),
        rotating_direction(random_rotation_direction()),
        position(Position2D(0, 0)) {}

  // Copy constructor
  Object(const Object &obj) = default;

  // Redefinition operator ==
  bool operator==(const Object &other) {
    return ((shape == other.get_shape()) &&
            (compare_colors(color, other.get_color())) &&
            (rotating_direction == other.get_rotating_direction()) &&
            (position == other.get_position()));
  }

  // Setters
  void set_position(const Position2D &pos) { position = pos; }

  // Getters
  Shape get_shape() const { return shape; }

  p6::Color get_color() const { return color; }

  int get_rotating_direction() const { return rotating_direction.direction; }

  Position2D get_position() const { return position; }
};

// set all postions of objects from a vector
inline void set_all_positions(std::vector<Object> &objects,
                              std::vector<Position2D> &positions) {
  for (int i = 0; i < objects.size(); i++) {
    objects[i].set_position(positions[i]);
  }
}

inline std::vector<Position2D> create_positions(std::vector<Object> &objects,
                                                int nb_objects_by_line) {
  std::vector<Position2D> positions;
  while (positions.size() < objects.size()) {
    const Position2D tmp = Position2D(random_position(nb_objects_by_line - 1),
                                      random_position(nb_objects_by_line - 1));
    if (std::find(positions.begin(), positions.end(), tmp) == positions.end()) {
      positions.push_back(tmp);
    }
  }
  return positions;
}