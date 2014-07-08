#include "mat.h"

namespace Geometry
{
  Mat::Mat(IntVector v1,IntVector v2, IntVector v3)
  {
    el(0,0) = v1[0];
    el(1,0) = v1[1];
    el(2,0) = v1[2];

    el(0,1) = v2[0];
    el(1,1) = v2[1];
    el(2,1) = v2[2];

    el(0,2) = v3[0];
    el(1,2) = v3[1];
    el(2,2) = v3[2];
  }
  double Mat::det()const
  {
    return el(0,0)*el(1,1)*el(2,2)+el(1,0)*el(2,1)*el(0,2)+el(0,1)*el(1,2)*el(2,0) - el(2,0)*el(1,1)*el(0,2)-el(1,0)*el(0,1)*el(2,2)-el(2,1)*el(1,2)*el(0,0);
  }
  void Mat::scale(double val)
  {
    for (int i =0; i <9; i++) 
    {
      double r = ar[i] * val;
      ar[i] = r;
      //BREAK_ON_LINE(ar[i] == r);
    }
  }
  Mat Mat::inverse()
  {
    Mat inv;
    inv.el(0,0) = (el(1,1) * el(2,2) - el(1,2) * el(2,1));
    inv.el(0,1) = (el(0,2) * el(2,1) - el(0,1) * el(2,2));
    inv.el(0,2) = (el(0,1) * el(1,2) - el(0,2) * el(1,1));

    inv.el(1,0) = (el(1,2) * el(2,0) - el(1,0) * el(2,2));
    inv.el(1,1) = (el(0,0) * el(2,2) - el(0,2) * el(2,0));
    inv.el(1,2) = (el(0,2) * el(1,0) - el(0,0) * el(1,2));

    inv.el(2,0) = (el(1,0) * el(2,1) - el(1,1) * el(2,0));
    inv.el(2,1) = (el(0,1) * el(2,0) - el(0,0) * el(2,1));
    inv.el(2,2) = (el(0,0) * el(1,1) - el(0,1) * el(1,0));
    inv.scale(1./det());
    return inv;
  }
  bool Mat::operator == (const Mat& m) const
  {
    for (int i=0;i<9;i++)
    {
      if (ar[i] != m.ar[i]) return false;
    }
    return true;
  }
  Mat Mat::operator * (const Mat& m) const
  {
    Mat n;
    for (int i=0;i<3;i++)
    {
      for (int j=0;j<3;j++)
      {
        n.el(i,j) = el(i,0) * m.el(0,j) + el(i,1) * m.el(1,j) + el(i,2) * m.el(2,j);
      }
    }
    return n;
  }

  IntVector Mat::operator * (const IntVector& v) const
  {
    IntVector o;
    o[0] = int(el(0,0) * v[0] + el(0,1) * v[1] + el(0,2) * v[2]);
    o[1] = int(el(1,0) * v[0] + el(1,1) * v[1] + el(1,2) * v[2]);
    o[2] = int(el(2,0) * v[0] + el(2,1) * v[1] + el(2,2) * v[2]);
    return o;
  }
}