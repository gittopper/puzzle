#pragma once

#include "base.h"
#include "geometry.h"


//test
namespace Geometry
{
	class Box
	{
	public:
		Box(int DX, int DY, int DZ);

		VolPart& el(const IntVector& coords)
		{
			return el(coords[0], coords[1], coords[2]);
		}

		VolPart& el(int x,int y,int z)
		{
			return box[x * dimZ * dimY + y * dimZ + z];
		}

		const VolPart& el(const IntVector& coords) const
		{
			return el(coords[0], coords[1], coords[2]);
		}

		const VolPart& el(int x,int y,int z) const
		{
			return box[x * dimZ * dimY + y * dimZ + z];
		}

	private:
		vector<VolPart> box;
		int dimX, dimY, dimZ;
	};
}