#pragma once

#include "rand.hpp"
#include "stats.hpp"
#include <p6/p6.h>
#include <vector>

struct Rotation {
  float rotation; // sens de rotation
  Rotation() : rotation(0) {}
  explicit Rotation(float _rotation) : rotation(_rotation){};
  bool operator==(const Rotation &other) const {
    return rotation == other.rotation;
  };
  bool operator==(const int other) const { return rotation == other; }
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

// bool compare_colors(const p6::Color &color1, const p6::Color &color2);

class Object {
private:
  Shape shape;
  p6::Color color;
  Rotation rotation;
  Position2D position;
  int color_index;

public:
  // Default constructor
  Object()
      : shape(Shape::CIRCLE), color(p6::Color(1.f, 0.f, 0.f)),
        rotation(Rotation()), position(Position2D(0, 0)){};

  // Constructor
  explicit Object(const std::vector<p6::Color> &colors,
                  const int nb_objects_by_line)
      : shape(static_cast<Shape>(random_shape(static_cast<int>(Shape::count)))),
        color_index(random_color(colors.size())), rotation(random_rotation()),
        position(Position2D(0, 0)) {
    color = colors[color_index];
  }

  // Constructor for the unique object, for Markov chains he keeps the lastest
  // shape in mind
  explicit Object(const std::vector<p6::Color> &colors,
                  const int nb_objects_by_line, int latest_shape)
      : shape(static_cast<Shape>(markov(latest_shape))),
        color_index(random_color(colors.size())), rotation(random_rotation()),
        position(Position2D(0, 0)) {
    color = colors[color_index];
  }

  // Copy constructor
  Object(const Object &obj) = default;

  // Redefinition operator ==
  bool operator==(const Object &other) {
    if (shape == Shape::CIRCLE) {
      return ((shape == other.get_shape()) &&
              (color_index == other.get_color_index()) &&
              (position == other.get_position()));
    }
    return ((shape == other.get_shape()) &&
            (color_index == other.get_color_index()) &&
            (abs(rotation.rotation - other.get_Rotation()) < 0.5) &&
            (position == other.get_position()));
  }

  // Setters
  void set_position(const Position2D &pos) { position = pos; }

  void set_color_difficult(const int unique_color,
                           const std::vector<p6::Color> &colors) {
    color_index = random_color(colors.size(), unique_color);
    color = colors[color_index];
  }

  // Getters
  Shape get_shape() const { return shape; }

  p6::Color get_color() const { return color; }

  int get_color_index() const { return color_index; }

  float get_Rotation() const { return rotation.rotation; }

  Position2D get_position() const { return position; }
};

// set all postions of objects from a vector
inline void set_all_positions(std::vector<Object> &objects,
                              std::vector<Position2D> &positions) {
  for (int i = 0; i < objects.size(); i++) {
    objects[i].set_position(positions[i]);
    update_stats(objects[i].get_position().x, objects[i].get_position().y,
                 objects[i].get_Rotation());
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