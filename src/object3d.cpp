#include "object3d.h"
#include <GL/gl.h>

namespace Geometry
{
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
    rotate(Mat::getRotated(dir, angle));
}

void Object3D::getMat44(float * f)
{
    f[0] = m.getVolPart(0, 0);
    f[4] = m.getVolPart(0, 1);
    f[8] = m.getVolPart(0, 2);

    f[1] = m.getVolPart(1, 0);
    f[5] = m.getVolPart(1, 1);
    f[9] = m.getVolPart(1, 2);

    f[2] = m.getVolPart(2, 0);
    f[6] = m.getVolPart(2, 1);
    f[10] = m.getVolPart(2, 2);

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

void Object3D::addChild(std::shared_ptr<Object3D> child)
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


}
