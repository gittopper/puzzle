#pragma once

#include "base.h"
#include "intvector.h"
#include "volpart.h"


//test
namespace Geometry
{
  class Box
  {
  public:
    Box(int DX, int DY, int DZ);

    VolPart& el(const IntVector& coords)
    {
      return el(coords[0], coords[1], coords[2]);
    }

    VolPart& el(int x,int y,int z)
    {
      return box[x * dimZ * dimY + y * dimZ + z];
    }

    int getDimX() const { return dimX;}
    int getDimY() const { return dimY;}
    int getDimZ() const { return dimZ;}

    const VolPart& el(const IntVector& coords) const
    {
      return el(coords[0], coords[1], coords[2]);
    }

    const VolPart& el(int x,int y,int z) const
    {
      return box[x * dimZ * dimY + y * dimZ + z];
    }

    void add(const vector<VolPart>& vols);

    void remove(const vector<VolPart>& vols);

    void rotate(Mat rot);

    bool isSqueezed(const VolPart& vol) const;

    bool isSqueezedV2(const VolPart& vol) const;

    bool checkHalf(const VolPart& vol) const;

    bool operator == (const Box& b) const { return box == b.box;}
  private:
    vector<VolPart> box;
    int dimX, dimY, dimZ;
  };
}