#pragma once

#include "base.h"
#include "geometry.h"


//test
namespace Geometry
{
	class Box
	{
	public:
		Box(int DX, int DY, int DZ):
		  dimX(DX),dimY(DY),dimZ(DZ){}
		VolPart& el(int x,y,z)
		{
			return box[x * dimZ * dimY + y * dimZ + z];
		}
	private:
		vector<VolPart> box;
		int dimX, dimY, dimZ;
	};
}