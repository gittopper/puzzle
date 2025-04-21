#pragma once

#include "geometry.h"
#include <glm/glm.hpp>


class Camera
{
public:
    Camera();

    enum DrugRegime {
        SHIFT,
        ROTATE
    };

    void setViewport(int w, int h);

    void rotate(float angleX, float angleY);

    void zoom(float z);

    void shiftStart(int x, int y);
    void shiftDrag(int x, int y);
    void shift(float dx, float dy);

    void rotateStart(int x, int y);
    void rotateDrag(int x, int y);
    void drag(int x, int y);
    void store();

    glm::mat4 viewMatrix() const;
    glm::mat4 projMatrix() const;

    std::vector<Geometry::Vector> overlayPoints();
    int width, height;
private:
    DrugRegime drug_regime_;
    Geometry::Vector eye, up, center;
    float scale;
    float fov_;
    int last_x_;
    int last_y_;
    int move_start_x_;
    int move_start_y_;
};
