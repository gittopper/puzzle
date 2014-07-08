#pragma once

#include "geometry.h"

namespace Geometry
{
  ostream& operator << (ostream& os, const IntVector& vec);

  ostream& operator << (ostream& os, const VolPart& v);

  ostream& operator << (ostream& os, const PuzzlePart& v);

  ostream& operator << (ostream& os, const vector<PuzzlePart>& v);

  ostream& operator << (ostream& os, const Box& b);
}