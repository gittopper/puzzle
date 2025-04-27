#include "camera.h"
#ifdef __ANDROID_API__

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#else

#include <GL/gl.h>
#include <GL/glut.h>

#endif
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(float fov) :
    eye_{0, 0, 10}, center_{0, 0, 0}, up_{0, 1, 0}, fov_{fov}, zoom_{1.} {
    store();
}

void Camera::setViewport(int w, int h) {
    width_ = w;
    height_ = h;
}

void Camera::shiftStart(int x, int y) {
    move_start_x_ = x;
    move_start_y_ = y;
    drag_regime_ = DragRegime::SHIFT;
}

void Camera::shiftDrag(int x, int y) {
    shift((x - move_start_x_) / 100., (move_start_y_ - y) / 100.);
}
void Camera::shift(float dx, float dy) {
    Geometry::Vector x =
        up_stored_.cross(eye_stored_ - center_stored_).normalized();
    auto shift = -x * dx - up_stored_ * dy;
    eye_ = eye_stored_ + shift;
    center_ = center_stored_ + shift;
}

void Camera::rotateStart(int x, int y) {
    move_start_x_ = x;
    move_start_y_ = y;
    drag_regime_ = DragRegime::ROTATE;
}
void Camera::rotateDrag(int x, int y) {
    float speed = 0.01f;
    float angleX = (x - move_start_x_) * speed;
    float angleY = -(y - move_start_y_) * speed;
    rotate(angleX, angleY);
}

void Camera::rotate(float angleX, float angleY) {
    Geometry::Mat rot(Geometry::Mat(cos(angleX), 0, sin(angleX), 0, 1, 0,
                                    -sin(angleX), 0, cos(angleX)) *
                      Geometry::Mat(1, 0, 0, 0, cos(angleY), sin(angleY), 0,
                                    -sin(angleY), cos(angleY)));

    Geometry::Vector x =
        up_stored_.cross(eye_stored_ - center_stored_).normalized();
    Geometry::Vector z = -x.cross(up_stored_);
    Geometry::Mat m = Geometry::Mat(x, up_stored_, z);
    Geometry::Mat tr = m * rot * m.inverse();
    eye_ = tr * (eye_stored_ - center_stored_) + center_stored_;
    up_ = tr * up_stored_;
}

void Camera::zoom(float z) {
    zoom_ *= z;
}

void Camera::zoomDrag() {
    eye_ += (eye_ - center_) * (zoom_ - 1);
}

void Camera::drag(int x, int y) {
    if (drag_regime_ == DragRegime::SHIFT) {
        shiftDrag(x, y);
    } else {
        rotateDrag(x, y);
    }
    if (zoom_ != 1.) {
        zoomDrag();
    }
}

void Camera::store() {
    eye_stored_ = eye_;
    up_stored_ = up_;
    center_stored_ = center_;
    zoom_ = 1.;
}

glm::mat4 Camera::projMatrix() const {
    float ratio = float(height_) / width_;

    return glm::perspective(glm::radians(fov_), 1 / ratio, 0.1f, 100.0f);
}

glm::mat4 Camera::mvp() const {
    auto proj = projMatrix();
    auto view = viewMatrix();
    return proj * view;
}

glm::mat4 Camera::viewMatrix() const {
    return glm::lookAt(glm::vec3(eye_[0], eye_[1], eye_[2]),
                       glm::vec3(center_[0], center_[1], center_[2]),
                       glm::vec3(up_[0], up_[1], up_[2]));
}

std::vector<Geometry::Vector> Camera::overlayPoints() {
    const auto view = viewMatrix();
    auto z_before = 0.1f;
    auto projection = projMatrix();
    auto pv = projection * view;
    auto pv_inv = glm::inverse(pv);
    auto z_overlay = 0.01f;
    auto coef = 1.;
    glm::vec4 lt{-1, 1, z_overlay, 1};
    glm::vec4 rt{1, 1, z_overlay, 1};
    glm::vec4 rb{1, -1, z_overlay, 1};
    glm::vec4 lb{-1, -1, z_overlay, 1};
    auto v0 = pv_inv * lt;
    auto a0 = glm::vec3(v0) / v0.w;
    auto v1 = pv_inv * rt;
    auto a1 = glm::vec3(v1) / v1.w;
    auto v2 = pv_inv * rb;
    auto a2 = glm::vec3(v2) / v2.w;
    auto v3 = pv_inv * lb;
    auto a3 = glm::vec3(v3) / v3.w;
    return {
        Geometry::Vector{a0.x, a0.y, a0.z}, Geometry::Vector{a1.x, a1.y, a1.z},
        Geometry::Vector{a2.x, a2.y, a2.z}, Geometry::Vector{a3.x, a3.y, a3.z}};
}
