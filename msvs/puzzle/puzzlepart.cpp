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
			box.merge((*it).xyz);
		}
		return;
	}
	PuzzlePart& PuzzlePart::shift(const IntVector& shift)
	{
		for (vector<VolPart>::iterator it = parts.begin(); it != parts.end(); it++)
		{
			(*it).xyz = (*it).xyz + shift;
		}
		return *this;
	}
	Mat PuzzlePart::getLCS()
	{
		IntVector x = parts[1].xyz - parts[0].xyz;
		IntVector y = parts[2].xyz - parts[0].xyz;
		return Mat(x,y,x.cross(y));
	}

	IntVector PuzzlePart::getZero()
	{
		return parts[0].xyz;
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