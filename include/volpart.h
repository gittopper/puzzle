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

    VolPart(VolType t, FloatVector coord, FloatVector iniDir = FloatVector(0,0,0), bool w = false):
      fillInfo(t),xyz(coord),dir(iniDir),wall(w){}

    bool operator==(const VolPart& vol) const;

    bool hasSide(int dim, int val) const;

    VolPart& operator+=(const VolPart& v);

	VolPart& shift(const FloatVector& shift);

	VolPart& rotate(RotType rot);

    VolPart& rotate(const Mat& m);

    VolPart& operator-=(const VolPart& another);

    bool couldPlace(const VolPart& another) const;

    bool shareOneOfSides(const VolPart& another) const;

    const FloatVector& getCoords() const { return xyz;}
    void setCoords(const FloatVector& coords) { xyz = coords;}

    const FloatVector& getDir() const { return dir;}
    void setDir(const FloatVector& d) { dir = d;}

    VolType type() const { return fillInfo;}
    void setType(VolType t) { fillInfo = t;}
  private:

    VolType fillInfo;
    FloatVector xyz, dir;
    bool wall;
  };
}