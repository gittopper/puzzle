#include "camera.h"
#include <GL/gl.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Geometry
{

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

void Camera::rotate(float angleX, float angleY)
{
    Geometry::Mat rot(Geometry::Mat(cos(angleX), 0, sin(angleX), 0, 1, 0, -sin(angleX), 0, cos(angleX)) *
                      Geometry::Mat(1, 0, 0, 0, cos(angleY), sin(angleY), 0, -sin(angleY), cos(angleY)));

    Vector x = up.cross(eye - center).normalized();
    Vector z = -x.cross(up);
    Geometry::Mat m = Geometry::Mat(x, up, z);
    Geometry::Mat tr = m * rot * m.inverse();
    eye = tr * (eye - center) + center;
    up = tr * up;
}


void Camera::render()
{
    //gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], up[0], up[1], up[2]);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glm::mat4 view       = glm::lookAt(
        glm::vec3(eye[0], eye[1], eye[2]),
        glm::vec3(center[0], center[1], center[2]),
        glm::vec3(up[0], up[1], up[2])
    );
    glMultMatrixf(&view[0][0]);


    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float ratio = float(height) / width;

    glm::mat4 projection = glm::perspective(glm::radians(fov_), 1 / ratio, 0.1f, 100.0f);
    glMultMatrixf(&projection[0][0]);

    //glOrtho(-scale, scale, -scale * ratio, scale * ratio, 10 * scale, -10 * scale);

}

std::vector<Vector>  Camera::overlayPoints() {
    glm::mat4 view       = glm::lookAt(
        glm::vec3(eye[0], eye[1], eye[2]),
        glm::vec3(center[0], center[1], center[2]),
        glm::vec3(up[0], up[1], up[2])
    );
    auto z_before = 0.1f;
    float ratio = float(height) / width;
    glm::mat4 projection = glm::perspective(glm::radians(fov_), 1 / ratio, z_before, 100.0f);
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
    return {Vector{a0.x, a0.y, a0.z},
    Vector{a1.x, a1.y, a1.z},
    Vector{a2.x, a2.y, a2.z},
    Vector{a3.x, a3.y, a3.z}};
}

void Camera::zoom(float zz)
{
    eye += (eye - center) * (zz - 1);
}
}
