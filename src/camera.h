#pragma once

#include <glm/glm.hpp>

#include "geometry.h"

class Camera {
  public:
    Camera(float fov = 55.);

    enum DrugRegime { SHIFT, ROTATE };

    void setViewport(int w, int h);

    void zoom(float zoom);
    void zoomDrag();

    void shiftStart(int x, int y);
    void shiftDrag(int x, int y);
    void shift(float dx, float dy);

    void rotateStart(int x, int y);
    void rotateDrag(int x, int y);
    void rotate(float angleX, float angleY);

    void drag(int x, int y);
    void store();

    int width() const {
        return width_;
    }
    int height() const {
        return height_;
    }

    glm::mat4 viewMatrix() const;
    glm::mat4 projMatrix() const;

    glm::mat4 mvp() const;

    std::vector<Geometry::Vector> overlayPoints();

  private:
    DrugRegime drug_regime_;
    Geometry::Vector eye_stored_, up_stored_, center_stored_;
    Geometry::Vector eye_, up_, center_;
    double zoom_;
    int width_, height_;
    float fov_;
    int move_start_x_;
    int move_start_y_;
};
