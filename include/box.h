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

		VolPart& el(int x,int y,int z)
		{
			return box[x * dimZ * dimY + y * dimZ + z];
		}
	private:
		vector<VolPart> box;
		int dimX, dimY, dimZ;
	};
}