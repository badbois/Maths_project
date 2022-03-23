#include <iostream>
#include <p6/p6.h>

#include <vector>

#include "Object.hpp"
#include "random.hpp"

enum class Color {
  RED,
  BLUE,
  YELLOW,
};

enum class Rotation {
  LEFT,
  RIGHT,
  NONE,
};

enum class Size {
  LITTLE,
  MEDIUM,
  LARGE,
};

enum class Shape {
  CIRCLE,
  SQUARE,
  TRIANGLE,
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
        position(_pos) {}
};

int probaUniform(std::vector<float> probas, std::vector<int> valeurs) {
  float rand = randomFloat<float>(0.f, 1.f);
  int i = 0;
  float proba = probas[0];
  while (rand > proba && i < probas.size() - 1) {
    proba += probas[i + 1];
    i++;
  }
  return valeurs[i];
}

int sensRotation() {
  std::vector<float> probas;
  std::vector<int> rotationSens;
  probas.push_back(0.3);
  probas.push_back(0.3);
  probas.push_back(0.4);
  rotationSens.push_back(-1);
  rotationSens.push_back(1);
  rotationSens.push_back(0);
  return probaUniform(probas, rotationSens);
}

int formeProbability() {
  std::vector<float> probas;
  std::vector<int> forme;
  probas.push_back(0.3);
  probas.push_back(0.3);
  probas.push_back(0.4);
  forme.push_back(0);
  forme.push_back(1);
  forme.push_back(2);
  return probaUniform(probas, forme);
}

void drawobject(p6::Context &ctx, float i, float j, p6::Angle rotation,
                int forme, int rotationSens) {
  switch (forme) {
  case 0:
    ctx.square(p6::Center{i, j}, p6::Radius{0.05f},
               p6::Rotation{rotationSens * rotation});
    break;
  case 1:
    ctx.circle(p6::Center{i, j}, p6::Radius{0.05f});
    break;
  }
}

void reinitialize(std::vector<int> &formes, std::vector<int> &sens) {
  for (int i = 0; i < formes.size(); i++) {
    formes[i] = formeProbability();
    sens[i] = sensRotation();
  }
}

int main() {
  auto ctx = p6::Context{{720, 720, "My p6 project"}};
  int nb_objects_by_line = 6;
  float pas = 2. / (nb_objects_by_line + 1);
  p6::Angle rotation = 0.011_turn;
  float time = 0;
  std::vector<int> formes(8 * 8);
  std::vector<int> sens(8 * 8);
  reinitialize(formes, sens);
  ctx.use_stroke = false;
  ctx.update = [&]() {
    ctx.background({0.2f, 0.1f, 0.3f});
    int k = 0;
    for (int i = 0; i < nb_objects_by_line; i += 1) {
      for (int j = 0; j < nb_objects_by_line; j += 1) {
        drawobject(ctx, -1 + (j + 1) * pas, -1 + (i + 1) * pas, rotation,
                   formes[k], sens[k]);
        k++;
        // ctx.square(p6::Center{i, j}, p6::Radius{0.05f},
        // p6::Rotation{rotation});
      }
    };
    time = ctx.time();
    rotation = time * 0.1_turn;
    ctx.circle(p6::Center{ctx.mouse()}, p6::Radius{0.03f});

    ctx.mouse_pressed = [&formes, &sens](p6::MouseButton) {
      reinitialize(formes, sens);
    };
  };
  ctx.start();
}