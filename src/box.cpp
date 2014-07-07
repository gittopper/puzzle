#include "box.h"

namespace Geometry
{
	Box::Box(int DX, int DY, int DZ):
	dimX(DX),dimY(DY),dimZ(DZ)
	{
		for(int i=0;i<DX;i++)
		{
			for(int j=0;j<DY;j++)
			{
				for(int k=0;k<DZ;k++)
				{
					box.push_back(VolPart(VolPart::Empty,IntVector(i,j,k)));
				}
			}
		}
	}
}
