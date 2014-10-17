#include "volpart.h"

namespace Geometry
{
  bool VolPart::operator==(const VolPart& vol) const
  {
    return xyz == vol.xyz && fillInfo == vol.fillInfo && ( fillInfo != Angle || dir == vol.dir); 
  }

  bool VolPart::hasSide(int dim, int val) const
  {
    if (fillInfo == Empty) return false;
    if (fillInfo == Full) return true;
    BREAK_ON_LINE(!dir[dim] || dir[dim] * dir[dim] == 1);
    return dir[dim] * (1 - 2 * val) >= 0;
  }

  VolPart& VolPart::shift(const Vector& shift)
  {
    xyz += shift;
    return *this;
  }

  VolPart& VolPart::operator+=(const VolPart& v)
  {
    BREAK_ON_LINE(xyz == v.xyz);
    if (fillInfo == Empty)
    {
      fillInfo = v.fillInfo;
      dir = v.dir;
      return *this;
    }
    if (fillInfo == Angle && v.fillInfo == Angle && dir == -v.dir)
    {
      fillInfo = Full;
      return *this;
    }
    BREAK_ON_LINE(false);
    return *this;
  }

  VolPart& VolPart::rotate(RotType rot)
  {
    BREAK_ON_LINE(fillInfo != Empty);
    xyz.rotate(rot);
    if (fillInfo == Angle) dir.rotate(rot);
    return *this;
  }

  VolPart& VolPart::rotate(const Mat& m)
  {
    xyz = m * xyz;
    if (fillInfo == Angle)  dir = m * dir;
    return *this;
  }

  VolPart& VolPart::operator-=(const VolPart& another)
  {
    if (fillInfo == Full)
    {
      if (another.fillInfo == Full)
      {
        fillInfo = Empty;
        return *this;
      }
      else if (another.fillInfo == Angle)
      {
        fillInfo = Angle;
        dir = -another.dir;
        return *this;
      }
      else
      {
        BREAK_ON_LINE(false);
      }
    }
    if (fillInfo == Angle)
    {
      if (another.fillInfo == Angle && dir == another.dir)
      {
        fillInfo = Empty;
        return *this;
      }
      else
      {
        BREAK_ON_LINE(false);
      }
    }
    return *this;
  }
  bool VolPart::couldPlace(const VolPart& another) const
  {
    BREAK_ON_LINE(xyz == another.xyz && another.fillInfo != Empty);
    return fillInfo == Empty
      || fillInfo == Angle && another.fillInfo == Angle && dir == -another.dir
      || fillInfo == Full && another.fillInfo == Empty; 
  }
  bool VolPart::shareOneOfSides(const VolPart& another) const
  {
    BREAK_ON_LINE(dot(xyz - another.xyz, xyz - another.xyz)<=1);

    if (fillInfo == Empty || another.fillInfo == Empty || wall || another.wall) return false;
    if (fillInfo == Full && another.fillInfo == Full) return true;
    if (fillInfo == Angle && another.fillInfo == Full)
    {
      return dot(dir, another.xyz - xyz) < 0;
    }
    if (fillInfo == Full && another.fillInfo == Angle)
    {
      return dot(another.dir, xyz - another.xyz) < 0;
    }
    if (fillInfo == Angle && another.fillInfo == Angle)
    {
      //return true;
      if (xyz == another.xyz)
      {
        if (dir == -another.dir) return true;
      }
      else
      {
        return dot(dir, another.xyz - xyz) < 0 && dot(another.dir, xyz - another.xyz) < 0;
      }
    }
    BREAK_ON_LINE(false);
    return false;
  }
}