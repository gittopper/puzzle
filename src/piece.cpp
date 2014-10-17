#include "piece.h"
#include <algorithm>

namespace Geometry
{
  Piece& Piece::rotate(RotType rot)
  {
    for (vector<VolPart>::iterator it = parts.begin(); it != parts.end(); it++)
    {
      (*it).rotate(rot);
    }
    return *this;
  }
  Piece& Piece::rotate(Mat rot)
  {
    for (vector<VolPart>::iterator it = parts.begin(); it != parts.end(); it++)
    {
      (*it).rotate(rot);
    }
    return *this;
  }
  bool Piece::operator == (const Piece& part) const
  {
    return parts == part.parts;
  }
  void Piece::getBBox(BBox& box) const 
  {
    for (vector<VolPart>::const_iterator it = parts.begin(); it != parts.end(); it++)
    {
      box.merge((*it).getCoords());
    }
    return;
  }
  Piece& Piece::shift(const Vector& shift)
  {
    for (vector<VolPart>::iterator it = parts.begin(); it != parts.end(); it++)
    {
      (*it).shift(shift);
    }
    return *this;
  }
  Mat Piece::getLCS() const
  {
    Vector x = parts[1].getCoords() - parts[0].getCoords();
    Vector y = parts[2].getCoords() - parts[0].getCoords();
    return Mat(x,y,x.cross(y));
  }

  Vector Piece::getZero() const
  {
    return parts[0].getCoords();
  }

  Piece& Piece::centralize()
  {
    BBox box;
    getBBox(box);
    shift(-box.minV);
    return *this;
  }
  Piece Piece::copy() const
  {
    return Piece(*this);
  }

  Mat Piece::getRotationMatrix(const Piece& part) const
  {
    Mat rot1 = getLCS();
    Mat rot2 = part.getLCS();

    Mat invRot1 = rot1.inverse();
    Mat res = rot2 * invRot1;
    BREAK_ON_LINE(res.det() == 1);
    return res;
  }

  bool PiecesSet::operator == (const PiecesSet& set) const
  {
    if (pieces.size() != set.pieces.size()) return false;
    for(unsigned i=0;i<pieces.size();i++)
    {
      if (pieces[i].number != set.pieces[i].number) return false;
    }

    Mat res = pieces[0].getRotationMatrix(set.pieces[0]);

    Vector prevShift = -pieces[0].getZero();
    Vector shift = set.pieces[0].getZero();

    bool theSame = true;

    for(unsigned i=0;i<set.pieces.size();i++)
    {
      Piece p = pieces[i];

      p.shift(prevShift);
      p.rotate(res);
      p.shift(shift);
      theSame = p == set.pieces[i];
      if (!theSame) break;
    }

    return theSame;
  }

  void PiecesSet::rotate(Mat rot)
  {
    for (vector<Piece>::iterator it = pieces.begin(); it != pieces.end(); it++)
    {
      (*it).rotate(rot);
    }
  }

  bool compNumbers (Piece i,Piece j) { return i.number < j.number; }

  void PiecesSet::order()
  {
    int maxn = 0;
    std::sort(pieces.begin(), pieces.end(), compNumbers);
  }

  void PiecesSet::shift(Vector v)
  {
    for (vector<Piece>::iterator it = pieces.begin(); it != pieces.end(); it++)
    {
      (*it).shift(v);
    }
  }

}
