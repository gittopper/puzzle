#include "intvector.h"
#include "mat.h"
#include "volpart.h"
#include "puzzlepart.h"
#include "bbox.h"
#include "box.h"

namespace Geometry
{
	IntVector operator * (const Mat& m, const IntVector& v);



	ostream& operator << (ostream& os, const IntVector& vec);

	ostream& operator << (ostream& os, const VolPart& v);

	ostream& operator << (ostream& os, const PuzzlePart& v);

	ostream& operator << (ostream& os, const vector<PuzzlePart>& v);

	ostream& operator << (ostream& os, const BOX& v);
}