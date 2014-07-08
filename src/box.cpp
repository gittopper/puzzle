#include "box.h"

namespace Geometry
{
  Box::Box(int DX, int DY, int DZ):
  dimX(DX),dimY(DY),dimZ(DZ)
  {
    for(int i=0;i<DX;i++)
    {
      for(int j=0;j<DY;j++)
      {
        for(int k=0;k<DZ;k++)
        {
          box.push_back(VolPart(VolPart::Empty,IntVector(i,j,k)));
        }
      }
    }
  }
  bool Box::isSqueezed(const VolPart& vol) const
  {
    if (vol.type() != VolPart::Angle) return false;
    BREAK_ON_LINE(!vol.getDir()[0] || !vol.getDir()[1] || !vol.getDir()[2]);
    int n = 0;
    if (vol.getDir()[0] != 0)
    {
      const VolPart& nVol = el(vol.getCoords()[0]+vol.getDir()[0], vol.getCoords()[1], vol.getCoords()[2]);
      if (nVol.type() == VolPart::Full)
      {
        n++;
      }
      else if (nVol.type() == VolPart::Angle)
      {
        if (vol.getDir()[0] * nVol.getDir()[0] >= 0)
        {
          n++;
        }
      }
    }
    if (vol.getDir()[1] != 0)
    {
      const VolPart& nVol = el(vol.getCoords()[0], vol.getCoords()[1]+vol.getDir()[1], vol.getCoords()[2]);
      if (nVol.type() == VolPart::Full)
      {
        n++;
      }
      else if (nVol.type() == VolPart::Angle)
      {
        if (vol.getDir()[1] * nVol.getDir()[1] >= 0)
        {
          n++;
        }
      }
    }
    if (vol.getDir()[2] != 0)
    {
      const VolPart& nVol = el(vol.getCoords()[0], vol.getCoords()[1], vol.getCoords()[2]+vol.getDir()[2]);
      if (nVol.type() == VolPart::Full)
      {
        n++;
      }
      else if (nVol.type() == VolPart::Angle)
      {
        if (vol.getDir()[2] * nVol.getDir()[2] >= 0)
        {
          n++;
        }
      }
    }
    return n>1;
  }
  bool Box::isSqueezedV2(const VolPart& vol) const
  {
    if (vol.type() != VolPart::Angle) return false;

    BREAK_ON_LINE(dot(vol.getDir(),vol.getDir()) == 2);
    int n = 0;
    if (vol.getDir()[0] > 0)
    {
      const VolPart& nVol = el(vol.getCoords()[0]+1, vol.getCoords()[1], vol.getCoords()[2]);
      if (nVol.type() == VolPart::Full)
      {
        n++;
      }
      else if (nVol.hasSide(0,0)) n++;
    }
    if (vol.getDir()[0] < 0)
    {
      const VolPart& nVol = el(vol.getCoords()[0]-1, vol.getCoords()[1], vol.getCoords()[2]);
      if (nVol.type() == VolPart::Full || nVol.hasSide(0,1))
      {
        n++;
      }
    }

    if (vol.getDir()[1] > 0)
    {
      const VolPart& nVol = el(vol.getCoords()[0], vol.getCoords()[1]+1, vol.getCoords()[2]);
      if (nVol.type() == VolPart::Full || nVol.hasSide(1,0))
      {
        n++;
      }
    }
    if (vol.getDir()[1] < 0)
    {
      const VolPart& nVol = el(vol.getCoords()[0], vol.getCoords()[1]-1, vol.getCoords()[2]);
      if (nVol.type() == VolPart::Full || nVol.hasSide(1,1))
      {
        n++;
      }
    }

    if (vol.getDir()[2] > 0)
    {
      const VolPart& nVol = el(vol.getCoords()[0], vol.getCoords()[1], vol.getCoords()[2]+1);
      if (nVol.type() == VolPart::Full || nVol.hasSide(2,0))
      {
        n++;
      }
    }
    if (vol.getDir()[2] < 0)
    {
      const VolPart& nVol = el(vol.getCoords()[0], vol.getCoords()[1], vol.getCoords()[2]-1);
      if (nVol.type() == VolPart::Full || nVol.hasSide(2,1))
      {
        n++;
      }
    }

    return n > 1;
  }

  void Box::add(const vector<VolPart>& vols)
  {
    for(unsigned i = 0; i < vols.size(); i++)
    {
      el(vols[i].getCoords()) += vols[i];
    }
  }

  void Box::remove(const vector<VolPart>& vols)
  {
    for(unsigned i = 0; i < vols.size(); i++)
    {
      el(vols[i].getCoords()) -= vols[i];
    }
  }

  bool Box::checkHalf(const VolPart& vol) const
  {
    int x = vol.getCoords()[0];
    int y = vol.getCoords()[1];
    int z = vol.getCoords()[2];
    return 
      el(x-1, y, z).type() == VolPart::Angle && el(x-1, y, z).getDir()[0]>0 ||
      el(x+1, y, z).type() == VolPart::Angle && el(x+1, y, z).getDir()[0]<0 ||
      el(x, y-1, z).type() == VolPart::Angle && el(x, y-1, z).getDir()[1]>0 ||
      el(x, y+1, z).type() == VolPart::Angle && el(x, y+1, z).getDir()[1]<0 ||
      el(x, y, z-1).type() == VolPart::Angle && el(x, y, z-1).getDir()[2]>0 ||
      el(x, y, z+1).type() == VolPart::Angle && el(x, y, z+1).getDir()[2]<0;
  }
}