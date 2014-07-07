#include "geometry.h"

namespace Geometry
{

	ostream& operator << (ostream& os, const IntVector& vec)
	{
		cout << "(" << vec[0] << "," << vec[1] << "," << vec[2] << ")";
		return os;
	}

	ostream& operator << (ostream& os, const VolPart& v)
	{
		cout<<(fillInfo == Empty ? "Empty" : fillInfo == Full ? "Full" : "Angle");
		cout<<xyz;
		if (fillInfo == Angle) cout<<","<<dir;
		return os;
	}

	ostream& operator << (ostream& os, const PuzzlePart& v)
	{
		v.print();
		return os;
	}

	ostream& operator << (ostream& os, const vector<PuzzlePart>& v)
	{
		for(vector<PuzzlePart>::const_iterator it = v.cbegin(); it != v.cend(); it++)
		{
			cout << *it;
		}
		return os;
	}


	ostream& operator << (ostream& os, const BOX& v)
	{
		int dimX = v.size();
		int dimY = v[0].size();
		int dimZ = v[0][0].size();
		for(int x = dimX - 1; x >= 0; x--)
		{
			for(int z = dimZ - 1; z >= 0; z--)
			{
				for(int y = 0; y <= dimY - 1; y++)
				{
					VolPart::VolType t = v[x][y][z].fillInfo;
					char s = t == VolPart::Empty ? ' ' : t == VolPart::Full ? 178 : 176;
					//cout << v[i][j][k];
					cout << s;
				}
				cout << endl;
			}
			cout << endl << endl;
		}
		return os;
	}
}