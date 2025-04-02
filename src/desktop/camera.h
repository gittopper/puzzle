#pragma once

#include "geometry.h"

namespace Geometry
{
class Camera
{
public:
    Camera();

    void setViewport(int w, int h);

    void rotate(float angleX, float angleY);

    void zoom(float z);

    void render();
private:
    Vector eye, up, center;
    int width, height;
    float scale;
};
}
