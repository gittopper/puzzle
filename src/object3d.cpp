#include "object3d.h"
#include "windows.h"
#include <gl/GL.h>

void Object3D::move(Vector s)
{
  shift += s;
}

void Object3D::rotate(Mat rot)
{
  m = rot * m;
  shift = rot * shift;
}

void Object3D::rotate(Vector dir, float angle)
{
  rotate(m.rotate(dir, angle));
}

void Object3D::getMat44(float * f)
{
  f[0] = m.el(0, 0);
  f[4] = m.el(0, 1);
  f[8] = m.el(0, 2);

  f[1] = m.el(1, 0);
  f[5] = m.el(1, 1);
  f[9] = m.el(1, 2);

  f[2] = m.el(2, 0);
  f[6] = m.el(2, 1);
  f[10] = m.el(2, 2);

  f[12] = shift[0];
  f[13] = shift[1];
  f[14] = shift[2];

  f[15] = 1;

  f[3] = 0;
  f[7] = 0;
  f[11] = 0;
}

void Object3D::draw()
{
  glPushMatrix();

  float ar[16];
  getMat44(ar);
  glMultMatrixf(ar);

  render();

  for (auto it = children.begin(); it != children.end(); it++)
  {
    (*it)->draw();
  }

  glPopMatrix();
}

void Object3D::addChild(shared_ptr<Object3D> child)
{
  children.push_back(child);
}

void Object3D::scale(float s)
{
  m = m * s;
}

void Object3D::removeChildren()
{
  children.clear();
}


