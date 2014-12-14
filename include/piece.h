#pragma once

#include "vector.h"
#include "mat.h"
#include "volpart.h"
#include "bbox.h"
#include "box.h"

namespace Geometry
{
  class Piece
  {
  public:
    Piece(int n):
    number(n),busy(false){}

    Piece& rotate(RotType rot);

    Piece& rotate(Mat rot);

    bool operator == (const Piece& part) const;

    void getBBox(BBox& box) const;

    Piece& shift(const Vector& shift);

  Mat getRotationMatrix(const Piece& part) const;

    Mat getLCS() const;

    Vector getZero() const;

    Piece& centralize();

    Piece copy() const;


    bool busy;
    int number;
    vector<VolPart> parts;
  };

  class PiecesSet
  {
  public:
    Piece& operator[](int i){ return pieces[i];}
    const Piece& operator[](int i) const { return pieces[i];}
    unsigned size() const { return pieces.size();}
    bool operator == (const PiecesSet& vec2) const;
    void rotate(Mat rot);
    void shift(Vector v);
    void order();
    vector<Piece> pieces;
  };

}
