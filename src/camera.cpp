#include "camera.h"
#ifdef __ANDROID_API__

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#else

#include <GL/gl.h>
#include <GL/glut.h>

#endif
#include <glm/gtc/matrix_transform.hpp>


Camera::Camera():
    scale(10),
    eye{0, 0, 10},
    center{0, 0, 0},
    up{0, 1, 0},
    fov_{55.}
{

}

void Camera::setViewport(int w, int h)
{
    width = w;
    height = h;
    glViewport(0, 0, width, height);
}

void Camera::shiftStart(int x, int y) {
    move_start_x_ = x;
    move_start_y_ = y;
    drug_regime_ = DrugRegime::SHIFT;
}

void Camera::shiftDrag(int x, int y) {
    shift((x - move_start_x_) / 100., (move_start_y_ - y) / 100.);
    move_start_x_ = x;
    move_start_y_ = y;
}
void Camera::shift(float dx, float dy) {
    Geometry::Vector x = up.cross(eye - center).normalized();
    auto shift = -x * dx - up * dy;
    eye += shift;
    center += shift;
}

void Camera::rotateStart(int x, int y) {
    last_x_ = x;
    last_y_ = y;
    drug_regime_ = DrugRegime::ROTATE;
}
void Camera::rotateDrag(int x, int y) {
    float speed = 0.01f;
    float angleX = (x - last_x_) * speed;
    float angleY = -(y - last_y_) * speed;
    last_x_ = x;
    last_y_ = y;
    rotate(angleX, angleY);
}

void Camera::drag(int x, int y) {
    if (drug_regime_ == DrugRegime::SHIFT) {
        shiftDrag(x, y);
    } else {
        rotateDrag(x, y);
    }
}

void Camera::rotate(float angleX, float angleY)
{
    Geometry::Mat rot(Geometry::Mat(cos(angleX), 0, sin(angleX), 0, 1, 0, -sin(angleX), 0, cos(angleX)) *
                      Geometry::Mat(1, 0, 0, 0, cos(angleY), sin(angleY), 0, -sin(angleY), cos(angleY)));

    Geometry::Vector x = up.cross(eye - center).normalized();
    Geometry::Vector z = -x.cross(up);
    Geometry::Mat m = Geometry::Mat(x, up, z);
    Geometry::Mat tr = m * rot * m.inverse();
    eye = tr * (eye - center) + center;
    up = tr * up;
}

glm::mat4 Camera::projMatrix() const {
    float ratio = float(height) / width;

    return glm::perspective(glm::radians(fov_), 1 / ratio, 0.1f, 100.0f);

}

glm::mat4 Camera::viewMatrix() const {
    return glm::lookAt(
        glm::vec3(eye[0], eye[1], eye[2]),
        glm::vec3(center[0], center[1], center[2]),
        glm::vec3(up[0], up[1], up[2])
    );
}

std::vector<Geometry::Vector>  Camera::overlayPoints() {
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
    return {Geometry::Vector{a0.x, a0.y, a0.z},
    Geometry::Vector{a1.x, a1.y, a1.z},
    Geometry::Vector{a2.x, a2.y, a2.z},
    Geometry::Vector{a3.x, a3.y, a3.z}};
}

void Camera::zoom(float zz)
{
    eye += (eye - center) * (zz - 1);
}

