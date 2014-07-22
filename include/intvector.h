#pragma once

#include "base.h"

namespace Geometry
{
  enum RotType
  {
    None,
    RotateX,
    RotateY,
    RotateZ
  };

  class FloatVector
  {
  public:
    FloatVector(float i = 0, float j = 0, float k = 0);

    FloatVector cross(const FloatVector v);

    FloatVector& rotate(RotType rotation);

    const float& FloatVector::operator[](int i) const
    {
      return vec[i];
    }

    float& FloatVector::operator[](int i)
    {
      return vec[i];
    }

    FloatVector operator-(const FloatVector& v) const;

    bool operator==(const FloatVector& v) const;

    FloatVector operator-() const;

    FloatVector operator+(const FloatVector& v) const;

	FloatVector operator+=(const FloatVector& v);
  private:
    float vec[3];
  };


  float dot(const FloatVector& v1, const FloatVector& v2);
}
