#include "intvector.h"

namespace Geometry
{
  float dot(const FloatVector& v1, const FloatVector& v2)
  {
    return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
  }

  FloatVector::FloatVector(float i, float j, float k)
  {
    vec[0] = i;
    vec[1] = j;
    vec[2] = k;
  }

  FloatVector FloatVector::cross(const FloatVector v)
  {
    FloatVector r;
    r[0] = vec[1] * v.vec[2] - vec[2] * v.vec[1];
    r[1] = vec[2] * v.vec[0] - vec[0] * v.vec[2];
    r[2] = vec[0] * v.vec[1] - vec[1] * v.vec[0];
    return r;
  }
  FloatVector& FloatVector::rotate(RotType rotation)
  {
    float x = vec[0];
    float y = vec[1];
    float z = vec[2];

    switch(rotation)
    {
    case RotateX:
      vec[1] = z;
      vec[2] = -y;
      break;
    case RotateY:
      vec[0] = -z;
      vec[2] = x;
      break;
    case RotateZ:
      vec[0] = y;
      vec[1] = -x;
    };
    return *this;
  }
  FloatVector FloatVector::operator-(const FloatVector& v) const
  {
    return FloatVector(vec[0] - v[0], vec[1] - v[1], vec[2] - v[2]);
  }
  bool FloatVector::operator==(const FloatVector& v) const
  {
    return vec[0] == v[0] && vec[1] == v[1] && vec[2] == v[2];
  }
  FloatVector FloatVector::operator-() const
  {
    return FloatVector(-vec[0], -vec[1], -vec[2]);
  }
  FloatVector FloatVector::operator+(const FloatVector& v) const
  {
    return FloatVector(vec[0] + v[0], vec[1] + v[1], vec[2] + v[2]);
  }
  FloatVector FloatVector::operator+=(const FloatVector& v)
  {
	  vec[0] += v[0];
	  vec[1] += v[1];
	  vec[2] += v[2];
	  return *this;
  }
}
