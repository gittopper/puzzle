#include "ivolpartrenderer.h"


void IVolPartRenderer:: render(const Geometry::VolPart& vol_part, const Geometry::Vector& color) {
    Geometry::Vector verts[8];
    verts[0] = Geometry::Vector(0, 0, 0);
    verts[1] = Geometry::Vector(1, 0, 0);
    verts[2] = Geometry::Vector(1, 1, 0);
    verts[3] = Geometry::Vector(0, 1, 0);

    verts[4] = Geometry::Vector(0, 0, 1);
    verts[5] = Geometry::Vector(1, 0, 1);
    verts[6] = Geometry::Vector(1, 1, 1);
    verts[7] = Geometry::Vector(0, 1, 1);
    if (vol_part.type() == Geometry::VolPart::VolType::Empty) {
        return;
    }
    setColor(color);
    ////////////////////////////////
    if (vol_part.type() == Geometry::VolPart::VolType::Full || dot(vol_part.getDir(), Geometry::Vector(1, 0, 0)) > 0)
    {
        drawSquare(vol_part.getCoords(), verts[0], verts[3], verts[7], verts[4], Geometry::Vector(-1.0, 0.0, 0.0));
    }
    if (vol_part.type() == Geometry::VolPart::VolType::Full || dot(vol_part.getDir(), Geometry::Vector(1, 0, 0)) < 0)
    {
        drawSquare(vol_part.getCoords(), verts[1], verts[5], verts[6], verts[2], Geometry::Vector(1.0, 0.0, 0.0));
    }
    ////////////////////////////////
    if (vol_part.type() == Geometry::VolPart::VolType::Full || dot(vol_part.getDir(), Geometry::Vector(0, 1, 0)) > 0)
    {
        drawSquare(vol_part.getCoords(), verts[0], verts[4], verts[5], verts[1], Geometry::Vector(0.0, -1.0, 0.0));
    }
    if (vol_part.type() == Geometry::VolPart::VolType::Full || dot(vol_part.getDir(), Geometry::Vector(0, 1, 0)) < 0)
    {
        drawSquare(vol_part.getCoords(), verts[3], verts[2], verts[6], verts[7], Geometry::Vector(0.0, 1.0, 0.0));
    }
    ////////////////////////////////
    if (vol_part.type() == Geometry::VolPart::VolType::Full || dot(vol_part.getDir(), Geometry::Vector(0, 0, 1)) > 0)
    {
        drawSquare(vol_part.getCoords(), verts[0], verts[1], verts[2], verts[3], Geometry::Vector(0.0, 0.0, -1.0));
    }
    if (vol_part.type() == Geometry::VolPart::VolType::Full || dot(vol_part.getDir(), Geometry::Vector(0, 0, 1)) < 0)
    {
        drawSquare(vol_part.getCoords(), verts[4], verts[7], verts[6], verts[5], Geometry::Vector(0.0, 0.0, 1.0));
    }
    if (vol_part.type() == Geometry::VolPart::VolType::Angle)
    {
        ////////////////////////////////
        float s2 = sqrt(1 / 2.);
        const Geometry::Vector& dir = vol_part.getDir();
        if (dot(dir, Geometry::Vector(1, 1, 0)) == 2)
        {
            drawSquare(vol_part.getCoords(), verts[5], verts[7], verts[3], verts[1], Geometry::Vector(s2, s2, 0.0));
            drawTriangle(vol_part.getCoords(), Geometry::Vector(1, 0, 0), Geometry::Vector(0, 0, 0), Geometry::Vector(0, 1, 0), Geometry::Vector(0, 0, -1));
            drawTriangle(vol_part.getCoords(), Geometry::Vector(1, 0, 1), Geometry::Vector(0, 1, 1), Geometry::Vector(0, 0, 1), Geometry::Vector(0, 0, 1));
        }
        if (dot(dir, Geometry::Vector(1, 1, 0)) == -2)
        {
            drawSquare(vol_part.getCoords(), verts[1], verts[3], verts[7], verts[5], Geometry::Vector(-s2, -s2, 0.0));
            drawTriangle(vol_part.getCoords(), Geometry::Vector(1, 0, 0), Geometry::Vector(0, 1, 0), Geometry::Vector(1, 1, 0), Geometry::Vector(0, 0, -1));
            drawTriangle(vol_part.getCoords(), Geometry::Vector(1, 0, 1), Geometry::Vector(1, 1, 1), Geometry::Vector(0, 1, 1), Geometry::Vector(0, 0, 1));
        }
        if (dir[0] == 1 && dir[1] == -1)
        {
            drawSquare(vol_part.getCoords(), verts[4], verts[6], verts[2], verts[0], Geometry::Vector(s2, -s2, 0.0));
            drawTriangle(vol_part.getCoords(), Geometry::Vector(0, 0, 0), Geometry::Vector(0, 1, 0), Geometry::Vector(1, 1, 0), Geometry::Vector(0, 0, -1));
            drawTriangle(vol_part.getCoords(), Geometry::Vector(0, 0, 1), Geometry::Vector(1, 1, 1), Geometry::Vector(0, 1, 1), Geometry::Vector(0, 0, 1));
        }
        if (dir[0] == -1 && dir[1] == 1)
        {
            drawSquare(vol_part.getCoords(), verts[0], verts[2], verts[6], verts[4], Geometry::Vector(-s2, s2, 0.0));
            drawTriangle(vol_part.getCoords(), Geometry::Vector(0, 0, 0), Geometry::Vector(1, 1, 0), Geometry::Vector(1, 0, 0), Geometry::Vector(0, 0, -1));
            drawTriangle(vol_part.getCoords(), Geometry::Vector(0, 0, 1), Geometry::Vector(1, 0, 1), Geometry::Vector(1, 1, 1), Geometry::Vector(0, 0, 1));
        }
        ////////////////////////////////
        if (dot(dir, Geometry::Vector(1, 0, 1)) == 2)
        {
            drawSquare(vol_part.getCoords(), verts[4], verts[7], verts[2], verts[1], Geometry::Vector(s2, 0.0, s2));
            drawTriangle(vol_part.getCoords(), Geometry::Vector(0, 0, 1), Geometry::Vector(0, 0, 0), Geometry::Vector(1, 0, 0), Geometry::Vector(0, -1, 0));
            drawTriangle(vol_part.getCoords(), Geometry::Vector(0, 1, 1), Geometry::Vector(1, 1, 0), Geometry::Vector(0, 1, 0), Geometry::Vector(0, 1, 0));
        }
        if (dot(dir, Geometry::Vector(1, 0, 1)) == -2)
        {
            drawSquare(vol_part.getCoords(), verts[1], verts[2], verts[7], verts[4], Geometry::Vector(-s2, 0.0, -s2));
            drawTriangle(vol_part.getCoords(), Geometry::Vector(1, 0, 0), Geometry::Vector(1, 0, 1), Geometry::Vector(0, 0, 1), Geometry::Vector(0, -1, 0));
            drawTriangle(vol_part.getCoords(), Geometry::Vector(1, 1, 0), Geometry::Vector(0, 1, 1), Geometry::Vector(1, 1, 1), Geometry::Vector(0, 1, 0));
        }
        if (dir[0] == 1 && dir[2] == -1)
        {
            drawSquare(vol_part.getCoords(), verts[0], verts[5], verts[6], verts[3], Geometry::Vector(s2, 0.0, -s2));
            drawTriangle(vol_part.getCoords(), Geometry::Vector(1, 0, 1), Geometry::Vector(0, 0, 1), Geometry::Vector(0, 0, 0), Geometry::Vector(0, -1, 0));
            drawTriangle(vol_part.getCoords(), Geometry::Vector(1, 1, 1), Geometry::Vector(0, 1, 0), Geometry::Vector(0, 1, 1), Geometry::Vector(0, 1, 0));
        }
        if (dir[0] == -1 && dir[2] == 1)
        {
            drawSquare(vol_part.getCoords(), verts[3], verts[6], verts[5], verts[0], Geometry::Vector(-s2, 0.0, s2));
            drawTriangle(vol_part.getCoords(), Geometry::Vector(1, 0, 0), Geometry::Vector(1, 0, 1), Geometry::Vector(0, 0, 0), Geometry::Vector(0, -1, 0));
            drawTriangle(vol_part.getCoords(), Geometry::Vector(1, 1, 0), Geometry::Vector(0, 1, 0), Geometry::Vector(1, 1, 1), Geometry::Vector(0, 1, 0));
        }
        ////////////////////////////////
        if (dot(dir, Geometry::Vector(0, 1, 1)) == 2)
        {
            drawSquare(vol_part.getCoords(), verts[3], verts[2], verts[5], verts[4], Geometry::Vector(0.0, s2, s2));
            drawTriangle(vol_part.getCoords(), Geometry::Vector(0, 0, 0), Geometry::Vector(0, 0, 1), Geometry::Vector(0, 1, 0), Geometry::Vector(-1, 0, 0));
            drawTriangle(vol_part.getCoords(), Geometry::Vector(1, 0, 0), Geometry::Vector(1, 1, 0), Geometry::Vector(1, 0, 1), Geometry::Vector(1, 0, 0));
        }
        if (dot(dir, Geometry::Vector(0, 1, 1)) == -2)
        {
            drawSquare(vol_part.getCoords(), verts[4], verts[5], verts[2], verts[3], Geometry::Vector(0.0, -s2, -s2));
            drawTriangle(vol_part.getCoords(), Geometry::Vector(0, 0, 1), Geometry::Vector(0, 1, 1), Geometry::Vector(0, 1, 0), Geometry::Vector(-1, 0, 0));
            drawTriangle(vol_part.getCoords(), Geometry::Vector(1, 0, 1), Geometry::Vector(1, 1, 0), Geometry::Vector(1, 1, 1), Geometry::Vector(1, 0, 0));
        }
        if (dir[1] == 1 && dir[2] == -1)
        {
            drawSquare(vol_part.getCoords(), verts[1], verts[6], verts[7], verts[0], Geometry::Vector(0.0, s2, -s2));
            drawTriangle(vol_part.getCoords(), Geometry::Vector(0, 0, 0), Geometry::Vector(0, 0, 1), Geometry::Vector(0, 1, 1), Geometry::Vector(-1, 0, 0));
            drawTriangle(vol_part.getCoords(), Geometry::Vector(1, 0, 0), Geometry::Vector(1, 1, 1), Geometry::Vector(1, 0, 1), Geometry::Vector(1, 0, 0));
        }
        if (dir[1] == -1 && dir[2] == 1)
        {
            drawSquare(vol_part.getCoords(), verts[0], verts[7], verts[6], verts[1], Geometry::Vector(0.0, -s2, s2));
            drawTriangle(vol_part.getCoords(), Geometry::Vector(0, 0, 0), Geometry::Vector(0, 1, 1), Geometry::Vector(0, 1, 0), Geometry::Vector(-1, 0, 0));
            drawTriangle(vol_part.getCoords(), Geometry::Vector(1, 0, 0), Geometry::Vector(1, 1, 0), Geometry::Vector(1, 1, 1), Geometry::Vector(1, 0, 0));
        }
    }
}
