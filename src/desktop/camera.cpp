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
    up{0, 1, 0}
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

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1 / ratio, 0.1f, 100.0f);
    glMultMatrixf(&projection[0][0]);

    //glOrtho(-scale, scale, -scale * ratio, scale * ratio, 10 * scale, -10 * scale);

}


void Camera::zoom(float zz)
{
    eye += (eye - center) * (zz - 1);
}
}
