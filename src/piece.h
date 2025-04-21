#pragma once

#include "vector.h"
#include "mat.h"
#include "volpart.h"
#include "bbox.h"
#include "box.h"

namespace Geometry
{

using Bitset = std::vector<bool>;

class Piece
{
public:
    Piece(int n):
        id(n) {}

    Piece& rotate(RotType rot);

    Piece& rotate(Mat rot);

    bool operator == (const Piece& part) const;

    Piece& shift(const Vector& shift);

    Mat getRotationMatrix(const Piece& part) const;

    void addToBBox(BBox& bbox) const;

    BBox getBBox() const;

    Mat getLCS() const;

    Vector getZero() const;

    Piece& centralize();

    Piece copy() const;


    std::size_t id;
    std::vector<VolPart> parts;
};

class PiecesSet: public std::vector<Piece>
{
public:
    template<typename ...Args>
    PiecesSet(Args&&... args):
             std::vector<Piece>{std::forward<Args>(args)...}
    {}
    bool operator==(const PiecesSet& set) const;
    void rotate(Mat rot);
    void shift(Vector v);
    void order();
};

}
