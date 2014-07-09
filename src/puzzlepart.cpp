#include "puzzlepart.h"
#include <algorithm>

namespace Geometry
{
  PuzzlePart& PuzzlePart::rotate(RotType rot)
  {
    for (vector<VolPart>::iterator it = parts.begin(); it != parts.end(); it++)
    {
      (*it).rotate(rot);
    }
    return *this;
  }
  PuzzlePart& PuzzlePart::rotate(Mat rot)
  {
    for (vector<VolPart>::iterator it = parts.begin(); it != parts.end(); it++)
    {
      (*it).rotate(rot);
    }
    return *this;
  }
  bool PuzzlePart::operator == (const PuzzlePart& part) const
  {
    return parts == part.parts;
  }
  void PuzzlePart::getBBox(BBox& box) const 
  {
    for (vector<VolPart>::const_iterator it = parts.cbegin(); it != parts.cend(); it++)
    {
      box.merge((*it).getCoords());
    }
    return;
  }
  PuzzlePart& PuzzlePart::shift(const IntVector& shift)
  {
    for (vector<VolPart>::iterator it = parts.begin(); it != parts.end(); it++)
    {
      (*it).setCoords((*it).getCoords() + shift);
    }
    return *this;
  }
  Mat PuzzlePart::getLCS() const
  {
    IntVector x = parts[1].getCoords() - parts[0].getCoords();
    IntVector y = parts[2].getCoords() - parts[0].getCoords();
    return Mat(x,y,x.cross(y));
  }

  IntVector PuzzlePart::getZero() const
  {
    return parts[0].getCoords();
  }

  PuzzlePart& PuzzlePart::centralize()
  {
    BBox box;
    getBBox(box);
    shift(-box.minV);
    return *this;
  }
  PuzzlePart PuzzlePart::copy() const
  {
    return PuzzlePart(*this);
  }

  Mat PuzzlePart::getRotationMatrix(const PuzzlePart& part) const
  {
	  Mat rot1 = getLCS();
	  Mat rot2 = part.getLCS();

	  Mat invRot1 = rot1.inverse();
	  Mat res = rot2 * invRot1;
	  BREAK_ON_LINE(res.det() == 1);
	  return res;
  }

  bool PuzzlesSet::operator == (const PuzzlesSet& set) const
  {
    if (puzzles.size() != set.puzzles.size()) return false;
    for(unsigned i=0;i<puzzles.size();i++)
    {
      if (puzzles[i].number != set.puzzles[i].number) return false;
    }

    Mat res = puzzles[0].getRotationMatrix(set.puzzles[0]);

    IntVector prevShift = -puzzles[0].getZero();
    IntVector shift = set.puzzles[0].getZero();

    bool theSame = true;

    for(unsigned i=0;i<set.puzzles.size();i++)
    {
      PuzzlePart p = puzzles[i];

      p.shift(prevShift);
      p.rotate(res);
      p.shift(shift);
      theSame = p == set.puzzles[i];
      if (!theSame) break;
    }

    return theSame;
  }

  void PuzzlesSet::rotate(Mat rot)
  {
    for (vector<PuzzlePart>::iterator it = puzzles.begin(); it != puzzles.end(); it++)
    {
      (*it).rotate(rot);
    }
  }

  bool compNumbers (PuzzlePart i,PuzzlePart j) { return i.number < j.number; }

  void PuzzlesSet::order()
  {
    int maxn = 0;
    std::sort(puzzles.begin(), puzzles.end(), compNumbers);
  }
}