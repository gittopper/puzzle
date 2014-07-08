#include "puzzlepart.h"


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

  bool puzzlesCouldBeCombined(const vector<Geometry::PuzzlePart>& vec1, const vector<Geometry::PuzzlePart>& vec2)
  {
    if (vec1.size() != vec2.size()) return false;
    for(unsigned i=0;i<vec1.size();i++)
    {
      if (vec1[i].number != vec2[i].number) return false;
    }

    Mat res = vec1[0].getRotationMatrix(vec2[0]);

	IntVector prevShift = -vec1[0].getZero();
    IntVector shift = vec2[0].getZero();

    bool theSame = true;

    for(unsigned i=0;i<vec2.size();i++)
    {
      PuzzlePart p = vec1[i];

      p.shift(prevShift);
      p.rotate(res);
      p.shift(shift);
      theSame = p == vec2[i];
      if (!theSame) break;
    }

    return theSame;
  }
}