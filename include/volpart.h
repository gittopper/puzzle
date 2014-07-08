#pragma once

#include "base.h"
#include "intvector.h"
#include "mat.h"

namespace Geometry
{
  class VolPart
  {
  public:
    enum VolType
    {
      Empty,
      Full,
      Angle
    };

    VolPart(VolType t, IntVector coord, IntVector iniDir = IntVector(0,0,0), bool w = false):
      fillInfo(t),xyz(coord),dir(iniDir),wall(w){}

    bool operator==(const VolPart& vol) const;

    bool hasSide(int dim, int val) const;

    VolPart& operator+=(const VolPart& v);

    VolPart& rotate(RotType rot);

    VolPart& rotate(const Mat& m);

    VolPart& operator-=(const VolPart& another);

    bool couldPlace(const VolPart& another) const;

    bool match(const VolPart& another) const;

    bool shareOneOfSides(const VolPart& another) const;

    const IntVector& getCoords() const { return xyz;}
    void setCoords(const IntVector& coords) { xyz = coords;}

    const IntVector& getDir() const { return dir;}
    void setDir(const IntVector& d) { dir = d;}

    VolType type() const { return fillInfo;}
    void setType(VolType t) { fillInfo = t;}
  private:

    VolType fillInfo;
    IntVector xyz, dir;
    bool wall;
  };
}