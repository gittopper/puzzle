#include "pieceshower.h"
#include "piece.h"
#include "GL/gl.h"
#include "math.h"

using namespace Visualization;
using namespace Geometry;

namespace
{
void drawSquare(const Vector& shift, const Vector& v1, const Vector& v2, const Vector& v3, const Vector& v4, const Vector& n)
{
    glBegin(GL_POLYGON);
    glNormal3f(  n[0], n[1], n[2]);
    glVertex3f(  shift[0] + v1[0], shift[1] + v1[1], shift[2] + v1[2]);
    glVertex3f(  shift[0] + v2[0], shift[1] + v2[1], shift[2] + v2[2]);
    glVertex3f(  shift[0] + v3[0], shift[1] + v3[1], shift[2] + v3[2]);
    glVertex3f(  shift[0] + v4[0], shift[1] + v4[1], shift[2] + v4[2]);
    glEnd();
}

void drawTriangle(const Vector& shift, const Vector& v1, const Vector& v2, const Vector& v3, const Vector& n)
{
    glBegin(GL_TRIANGLES);
    glNormal3f(  n[0], n[1], n[2]);
    glVertex3f(  shift[0] + v1[0], shift[1] + v1[1], shift[2] + v1[2]);
    glVertex3f(  shift[0] + v2[0], shift[1] + v2[1], shift[2] + v2[2]);
    glVertex3f(  shift[0] + v3[0], shift[1] + v3[1], shift[2] + v3[2]);
    glEnd();
}
}

void PieceDrawer::draw(const Piece& part) const
{
    VolPartDrawer volPartDrawer;
    for (std::vector<VolPart>::const_iterator it = part.parts.begin(); it != part.parts.end(); ++it)
    {
        volPartDrawer.draw(*it);
    }
}

void VolPartDrawer::draw(const VolPart& v) const
{
    Vector verts[8];
    verts[0] = Vector(0, 0, 0);
    verts[1] = Vector(1, 0, 0);
    verts[2] = Vector(1, 1, 0);
    verts[3] = Vector(0, 1, 0);

    verts[4] = Vector(0, 0, 1);
    verts[5] = Vector(1, 0, 1);
    verts[6] = Vector(1, 1, 1);
    verts[7] = Vector(0, 1, 1);

    if (v.type() == VolPart::VolType::Empty) return;
    ////////////////////////////////
    if (v.type() == VolPart::VolType::Full || dot(v.getDir(), Vector(1, 0, 0)) > 0)
    {
        drawSquare(v.getCoords(), verts[0], verts[3], verts[7], verts[4], Vector(-1.0, 0.0, 0.0));
    }
    if (v.type() == VolPart::VolType::Full || dot(v.getDir(), Vector(1, 0, 0)) < 0)
    {
        drawSquare(v.getCoords(), verts[1], verts[5], verts[6], verts[2], Vector(1.0, 0.0, 0.0));
    }
    ////////////////////////////////
    if (v.type() == VolPart::VolType::Full || dot(v.getDir(), Vector(0, 1, 0)) > 0)
    {
        drawSquare(v.getCoords(), verts[0], verts[4], verts[5], verts[1], Vector(0.0, -1.0, 0.0));
    }
    if (v.type() == VolPart::VolType::Full || dot(v.getDir(), Vector(0, 1, 0)) < 0)
    {
        drawSquare(v.getCoords(), verts[3], verts[2], verts[6], verts[7], Vector(0.0, 1.0, 0.0));
    }
    ////////////////////////////////
    if (v.type() == VolPart::VolType::Full || dot(v.getDir(), Vector(0, 0, 1)) > 0)
    {
        drawSquare(v.getCoords(), verts[0], verts[1], verts[2], verts[3], Vector(0.0, 0.0, -1.0));
    }
    if (v.type() == VolPart::VolType::Full || dot(v.getDir(), Vector(0, 0, 1)) < 0)
    {
        drawSquare(v.getCoords(), verts[4], verts[7], verts[6], verts[5], Vector(0.0, 0.0, 1.0));
    }
    if (v.type() == VolPart::VolType::Angle)
    {
        ////////////////////////////////
        float s2 = sqrt(1 / 2.);
        const Vector& dir = v.getDir();
        if (dot(dir, Vector(1, 1, 0)) == 2)
        {
            drawSquare(v.getCoords(), verts[5], verts[7], verts[3], verts[1], Vector(s2, s2, 0.0));
            drawTriangle(v.getCoords(), Vector(1, 0, 0), Vector(0, 0, 0), Vector(0, 1, 0), Vector(0, 0, -1));
            drawTriangle(v.getCoords(), Vector(1, 0, 1), Vector(0, 1, 1), Vector(0, 0, 1), Vector(0, 0, 1));
        }
        if (dot(dir, Vector(1, 1, 0)) == -2)
        {
            drawSquare(v.getCoords(), verts[1], verts[3], verts[7], verts[5], Vector(-s2, -s2, 0.0));
            drawTriangle(v.getCoords(), Vector(1, 0, 0), Vector(0, 1, 0), Vector(1, 1, 0), Vector(0, 0, -1));
            drawTriangle(v.getCoords(), Vector(1, 0, 1), Vector(1, 1, 1), Vector(0, 1, 1), Vector(0, 0, 1));
        }
        if (dir[0] == 1 && dir[1] == -1)
        {
            drawSquare(v.getCoords(), verts[4], verts[6], verts[2], verts[0], Vector(s2, -s2, 0.0));
            drawTriangle(v.getCoords(), Vector(0, 0, 0), Vector(0, 1, 0), Vector(1, 1, 0), Vector(0, 0, -1));
            drawTriangle(v.getCoords(), Vector(0, 0, 1), Vector(1, 1, 1), Vector(0, 1, 1), Vector(0, 0, 1));
        }
        if (dir[0] == -1 && dir[1] == 1)
        {
            drawSquare(v.getCoords(), verts[0], verts[2], verts[6], verts[4], Vector(-s2, s2, 0.0));
            drawTriangle(v.getCoords(), Vector(0, 0, 0), Vector(1, 1, 0), Vector(1, 0, 0), Vector(0, 0, -1));
            drawTriangle(v.getCoords(), Vector(0, 0, 1), Vector(1, 0, 1), Vector(1, 1, 1), Vector(0, 0, 1));
        }
        ////////////////////////////////
        if (dot(dir, Vector(1, 0, 1)) == 2)
        {
            drawSquare(v.getCoords(), verts[4], verts[7], verts[2], verts[1], Vector(s2, 0.0, s2));
            drawTriangle(v.getCoords(), Vector(0, 0, 1), Vector(0, 0, 0), Vector(1, 0, 0), Vector(0, -1, 0));
            drawTriangle(v.getCoords(), Vector(0, 1, 1), Vector(1, 1, 0), Vector(0, 1, 0), Vector(0, 1, 0));
        }
        if (dot(dir, Vector(1, 0, 1)) == -2)
        {
            drawSquare(v.getCoords(), verts[1], verts[2], verts[7], verts[4], Vector(-s2, 0.0, -s2));
            drawTriangle(v.getCoords(), Vector(1, 0, 0), Vector(1, 0, 1), Vector(0, 0, 1), Vector(0, -1, 0));
            drawTriangle(v.getCoords(), Vector(1, 1, 0), Vector(0, 1, 1), Vector(1, 1, 1), Vector(0, 1, 0));
        }
        if (dir[0] == 1 && dir[2] == -1)
        {
            drawSquare(v.getCoords(), verts[0], verts[5], verts[6], verts[3], Vector(s2, 0.0, -s2));
            drawTriangle(v.getCoords(), Vector(1, 0, 1), Vector(0, 0, 1), Vector(0, 0, 0), Vector(0, -1, 0));
            drawTriangle(v.getCoords(), Vector(1, 1, 1), Vector(0, 1, 0), Vector(0, 1, 1), Vector(0, 1, 0));
        }
        if (dir[0] == -1 && dir[2] == 1)
        {
            drawSquare(v.getCoords(), verts[3], verts[6], verts[5], verts[0], Vector(-s2, 0.0, s2));
            drawTriangle(v.getCoords(), Vector(1, 0, 0), Vector(1, 0, 1), Vector(0, 0, 0), Vector(0, -1, 0));
            drawTriangle(v.getCoords(), Vector(1, 1, 0), Vector(0, 1, 0), Vector(1, 1, 1), Vector(0, 1, 0));
        }
        ////////////////////////////////
        if (dot(dir, Vector(0, 1, 1)) == 2)
        {
            drawSquare(v.getCoords(), verts[3], verts[2], verts[5], verts[4], Vector(0.0, s2, s2));
            drawTriangle(v.getCoords(), Vector(0, 0, 0), Vector(0, 0, 1), Vector(0, 1, 0), Vector(-1, 0, 0));
            drawTriangle(v.getCoords(), Vector(1, 0, 0), Vector(1, 1, 0), Vector(1, 0, 1), Vector(1, 0, 0));
        }
        if (dot(dir, Vector(0, 1, 1)) == -2)
        {
            drawSquare(v.getCoords(), verts[4], verts[5], verts[2], verts[3], Vector(0.0, -s2, -s2));
            drawTriangle(v.getCoords(), Vector(0, 0, 1), Vector(0, 1, 1), Vector(0, 1, 0), Vector(-1, 0, 0));
            drawTriangle(v.getCoords(), Vector(1, 0, 1), Vector(1, 1, 0), Vector(1, 1, 1), Vector(1, 0, 0));
        }
        if (dir[1] == 1 && dir[2] == -1)
        {
            drawSquare(v.getCoords(), verts[1], verts[6], verts[7], verts[0], Vector(0.0, s2, -s2));
            drawTriangle(v.getCoords(), Vector(0, 0, 0), Vector(0, 0, 1), Vector(0, 1, 1), Vector(-1, 0, 0));
            drawTriangle(v.getCoords(), Vector(1, 0, 0), Vector(1, 1, 1), Vector(1, 0, 1), Vector(1, 0, 0));
        }
        if (dir[1] == -1 && dir[2] == 1)
        {
            drawSquare(v.getCoords(), verts[0], verts[7], verts[6], verts[1], Vector(0.0, -s2, s2));
            drawTriangle(v.getCoords(), Vector(0, 0, 0), Vector(0, 1, 1), Vector(0, 1, 0), Vector(-1, 0, 0));
            drawTriangle(v.getCoords(), Vector(1, 0, 0), Vector(1, 1, 0), Vector(1, 1, 1), Vector(1, 0, 0));
        }
    }
}


void PiecesSetShower::draw(const Geometry::PiecesSet& pieces) const
{
    for (int i = 0; i < pieces.pieces.size(); i++)
    {
        Piece p = pieces.pieces[i];
        partDrawer.draw(p);
    }
}

