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
  Mat PuzzlePart::getLCS()
  {
    IntVector x = parts[1].getCoords() - parts[0].getCoords();
    IntVector y = parts[2].getCoords() - parts[0].getCoords();
    return Mat(x,y,x.cross(y));
  }

  IntVector PuzzlePart::getZero()
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
}