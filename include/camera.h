#pragma once

#include "geometry.h"
#include "object3d.h"

class Camera
{
public:
  Camera();

  void setViewport(int w, int h);

  void setScale(float s);

  void zoom(float z);

  void setPosition(Vector dir, Vector center, Vector up);

  void render();
private:
  Vector dir, up, c;
  float w, h, z, scale;
};