#include "tests.h"

#include "utils.h"

using namespace Geometry;

PiecesSet generateTestPuzzles() {
    PiecesSet pieces;

    Piece p1(1);
    p1.parts.push_back(VolPart(VolPart::VolType::Full, Vector(0, 0, 0)));
    p1.parts.push_back(
        VolPart(VolPart::VolType::Angle, Vector(0, 1, 0), Vector(0, 1, -1)));
    pieces.push_back(p1);

    Piece p2(2);
    p2.parts.push_back(VolPart(VolPart::VolType::Full, Vector(0, 0, 0)));
    p2.parts.push_back(VolPart(VolPart::VolType::Full, Vector(0, 1, 0)));
    p2.parts.push_back(VolPart(VolPart::VolType::Full, Vector(0, 0, 1)));
    p2.parts.push_back(
        VolPart(VolPart::VolType::Angle, Vector(0, 1, 1), Vector(-1, 0, 1)));
    pieces.push_back(p2);

    Piece p3(3);
    p3.parts.push_back(VolPart(VolPart::VolType::Full, Vector(0, 0, 0)));
    p3.parts.push_back(VolPart(VolPart::VolType::Full, Vector(0, 0, 1)));
    p3.parts.push_back(
        VolPart(VolPart::VolType::Angle, Vector(0, 1, 0), Vector(1, 1, 0)));
    p3.parts.push_back(
        VolPart(VolPart::VolType::Angle, Vector(1, 0, 1), Vector(1, 0, -1)));
    pieces.push_back(p3);

    return pieces;
}

bool makeGeneralTests() {
    BREAK_ON_LINE(Vector(0, 0, 1).rotate(RotateX) == Vector(0, 1, 0));
    BREAK_ON_LINE(Vector(0, 0, 1).rotate(RotateX).rotate(RotateX) ==
                  Vector(0, 0, -1));

    BREAK_ON_LINE(Vector(1, 0, 0).rotate(RotateY) == Vector(0, 0, 1));
    BREAK_ON_LINE(Vector(1, 0, 0).rotate(RotateY).rotate(RotateY) ==
                  Vector(-1, 0, 0));

    BREAK_ON_LINE(Vector(0, 1, 0).rotate(RotateZ) == Vector(1, 0, 0));
    BREAK_ON_LINE(Vector(0, 1, 0).rotate(RotateZ).rotate(RotateZ) ==
                  Vector(0, -1, 0));

    PiecesSet pieces = generateWoodPuzzles();
    Piece part = pieces[0];
    part.rotate(RotateX);
    part.centralize();

    Piece p1(1);
    p1.parts.push_back(VolPart(VolPart::VolType::Full, Vector(0, 0, 1)));
    p1.parts.push_back(VolPart(VolPart::VolType::Full, Vector(0, 1, 0)));
    p1.parts.push_back(
        VolPart(VolPart::VolType::Angle, Vector(0, 0, 0), Vector(1, 0, -1)));
    p1.parts.push_back(
        VolPart(VolPart::VolType::Angle, Vector(0, 1, 1), Vector(0, 1, 1)));

    bool areEqual = part == p1;
    BREAK_ON_LINE(areEqual);

    Mat m(Vector(0, -1, 0), Vector(0, 0, 1), Vector(1, 0, 0));

    Mat rotX(1, 0, 0, 0, 0, -1, 0, 1, 0);
    Mat rotZ(0, -1, 0, 1, 0, 0, 0, 0, 1);

    PiecesSet rotatedPuzzles = pieces;
    rotatedPuzzles.rotate(rotX);
    BREAK_ON_LINE(rotatedPuzzles == pieces);
    rotatedPuzzles.rotate(rotZ);
    BREAK_ON_LINE(rotatedPuzzles == pieces);

    Mat r = m * m.inverse();
    Mat e(Vector(1, 0, 0), Vector(0, 1, 0), Vector(0, 0, 1));
    BREAK_ON_LINE(r == e);
    Vector v = e * Vector(-1, 1, 2);
    BREAK_ON_LINE(v == Vector(-1, 1, 2));
    return true;
}
