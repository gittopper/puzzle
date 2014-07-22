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

    PuzzlePart& shift(const FloatVector& shift);

	Mat getRotationMatrix(const PuzzlePart& part) const;

    Mat getLCS() const;

    FloatVector getZero() const;

    PuzzlePart& centralize();

    PuzzlePart copy() const;


    bool busy;
    int number;
    vector<VolPart> parts;
  };

  class PuzzlesSet
  {
  public:
    PuzzlePart& operator[](int i){ return puzzles[i];}
    const PuzzlePart& operator[](int i) const { return puzzles[i];}
    unsigned size() const { return puzzles.size();}
    bool operator == (const PuzzlesSet& vec2) const;
    void rotate(Mat rot);
    void order();
    vector<PuzzlePart> puzzles;
  };

}