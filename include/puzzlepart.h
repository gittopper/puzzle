#pragma once

#include "intvector.h"
#include "mat.h"
#include "volpart.h"
#include "bbox.h"
#include "box.h"

namespace Geometry
{
  class PuzzlePart
  {
  public:
    PuzzlePart(int n):
    number(n),busy(false){}

    PuzzlePart& rotate(RotType rot);

    PuzzlePart& rotate(Mat rot);

    bool operator == (const PuzzlePart& part) const;

    void getBBox(BBox& box) const;

    PuzzlePart& shift(const IntVector& shift);

    Mat getLCS();

    IntVector getZero();

    PuzzlePart& centralize();

    PuzzlePart copy() const;


    bool busy;
    int number;
    vector<VolPart> parts;
  };
}