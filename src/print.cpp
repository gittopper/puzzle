#include "geometry.h"

namespace Geometry
{

  ostream& operator << (ostream& os, const FloatVector& vec)
  {
    cout << "(" << vec[0] << "," << vec[1] << "," << vec[2] << ")";
    return os;
  }

  ostream& operator << (ostream& os, const VolPart& v)
  {
    cout<<(v.type() == VolPart::Empty ? "Empty" : v.type() == VolPart::Full ? "Full" : "Angle");
    cout<<v.getCoords();
    if (v.type() == VolPart::Angle) cout << "," << v.getDir();
    return os;
  }

  ostream& operator << (ostream& os, const PuzzlePart& p)
  {
    cout<<"Part number "<<p.number<<":"<<endl;
    for (vector<VolPart>::const_iterator it = p.parts.cbegin(); it != p.parts.cend(); it++)
    {
      cout<<*it<<endl;
    }
    cout<<endl;
    return os;
  }

  ostream& operator << (ostream& os, const PuzzlesSet& v)
  {
    for(unsigned i = 0; i < v.size(); i++)
    {
      cout << v[i];
    }
    return os;
  }


  ostream& operator << (ostream& os, const Box& b)
  {
    int dimX = b.getDimX();
    int dimY = b.getDimY();
    int dimZ = b.getDimZ();
    for(int z = dimZ - 1; z >= 0; z--)
    {
      for(int x = dimX - 1; x >= 0; x--)
      {
        for(int y = 0; y <= dimY - 1; y++)
        {
          VolPart::VolType t = b.el(x, y, z).type();
          char s = t == VolPart::Empty ? ' ' : t == VolPart::Full ? 178 : 176;
          //cout << b.el(x,y,z);
          cout << s;
        }
        cout << " ";
      }
      cout << endl;
    }
    return os;
  }
}