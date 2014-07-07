#pragma once

#include "base.h"
#include "intvector.h"
#include "mat.h"

namespace Geometry
{
	class VolPart
	{
	public:
		enum VolType
		{
			Empty,
			Full,
			Angle
		};

		VolPart(VolType t, IntVector coord, IntVector iniDir = IntVector(0,0,0), bool w = false):
			fillInfo(t),xyz(coord),dir(iniDir),wall(w){}

		bool operator==(const VolPart& vol) const;

		bool hasSide(int dim, int val) const;

		VolPart& operator+=(const VolPart& v);

		VolPart& rotate(RotType rot);

		VolPart& rotate(const Mat& m);

		VolPart& operator-=(const VolPart& another);

		bool couldPlace(const VolPart& another) const;

		bool match(const VolPart& another) const;

		bool shareOneOfSides(const VolPart& another) const;

		IntVector& getCoords() { return xyz;}
		const IntVector& getCoords() const { return xyz;}

		IntVector& getDir() { return dir;}
		const IntVector& getDir() const { return dir;}
	private:

		VolType fillInfo;
		IntVector xyz, dir;
		bool wall;
	};
}