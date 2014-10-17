#include "camera.h"
#include "windows.h"
#include "gl/GLU.h"

Camera::Camera()
{

}

void Camera::setViewport(int wNew, int hNew)
{
  float wd = (wNew - w) / 2.;
  float hd = (hNew - h) / 2.;
  w = wNew;
  h = hNew;
}

void Camera::setPosition(Vector d, Vector center, Vector upNew)
{
  dir = - d.normalized();
  up = upNew.ortogonal(d).normalized();
  c = center;
}

void Camera::render()
{
  glViewport(0, 0, w, h);

  gluLookAt(dir[0], dir[1], dir[2], c[0], c[1], c[2], up[0], up[1], up[2]);
  float s = scale / 2.;
}

void Camera::setScale(float s)
{
  scale = s;
}

void Camera::zoom(float zz)
{
  z = zz;
}
