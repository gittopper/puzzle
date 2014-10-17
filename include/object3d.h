#pragma once

#include "geometry.h"
#include <memory>

using namespace Geometry;


class Object3D
{
public:
  Object3D(){}

  void move(Vector shift);
  void rotate(Mat rot);
  void scale(float s);
  void rotate(Vector dir, float angle);

  void draw();
  virtual void render() = 0;

  void addChild(shared_ptr<Object3D> child);
  void removeChildren();

  virtual ~Object3D(){}
protected:
  void getMat44(float * f);
  Mat m;
  Vector shift;
  std::vector<shared_ptr<Object3D>> children;
};

