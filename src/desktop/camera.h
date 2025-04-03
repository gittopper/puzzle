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
    std::vector<Vector> overlayPoints();
    int width, height;
private:
    Vector eye, up, center;
    float scale;
};
}
