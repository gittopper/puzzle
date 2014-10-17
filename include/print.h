#pragma once

#include "geometry.h"

namespace Geometry
{
  ostream& operator << (ostream& os, const Vector& vec);

  ostream& operator << (ostream& os, const VolPart& v);

  ostream& operator << (ostream& os, const Piece& v);

  ostream& operator << (ostream& os, const PiecesSet& v);

  ostream& operator << (ostream& os, const Box& b);
}