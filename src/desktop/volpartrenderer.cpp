#include "volpartrenderer.h"

#include "GL/gl.h"
#include "math.h"
#include "piece.h"

void VolPartRenderer::drawSquare(const Geometry::Vector& shift,
                                 const Geometry::Vector& v1,
                                 const Geometry::Vector& v2,
                                 const Geometry::Vector& v3,
                                 const Geometry::Vector& v4,
                                 const Geometry::Vector& n) const {
    glBegin(GL_POLYGON);
    glNormal3f(n[0], n[1], n[2]);
    glVertex3f(shift[0] + v1[0], shift[1] + v1[1], shift[2] + v1[2]);
    glVertex3f(shift[0] + v2[0], shift[1] + v2[1], shift[2] + v2[2]);
    glVertex3f(shift[0] + v3[0], shift[1] + v3[1], shift[2] + v3[2]);
    glVertex3f(shift[0] + v4[0], shift[1] + v4[1], shift[2] + v4[2]);
    glEnd();
}

void VolPartRenderer::drawTriangle(const Geometry::Vector& shift,
                                   const Geometry::Vector& v1,
                                   const Geometry::Vector& v2,
                                   const Geometry::Vector& v3,
                                   const Geometry::Vector& n) const {
    glBegin(GL_TRIANGLES);
    glNormal3f(n[0], n[1], n[2]);
    glVertex3f(shift[0] + v1[0], shift[1] + v1[1], shift[2] + v1[2]);
    glVertex3f(shift[0] + v2[0], shift[1] + v2[1], shift[2] + v2[2]);
    glVertex3f(shift[0] + v3[0], shift[1] + v3[1], shift[2] + v3[2]);
    glEnd();
}

void VolPartRenderer::setColor(const Geometry::Vector& color) const {
    glColor3f(color[0], color[1], color[2]);
}
