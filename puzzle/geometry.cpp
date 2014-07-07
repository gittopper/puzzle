#include "geometry.h"

namespace Geometry
{

	IntVector operator * (const Mat& m, const IntVector& v)
	{
		IntVector o;
		o[0] = int(m.el(0,0) *v[0] + m.el(0,1) *v[1] + m.el(0,2) *v[2]);
		o[1] = int(m.el(1,0) *v[0] + m.el(1,1) *v[1] + m.el(1,2) *v[2]);
		o[2] = int(m.el(2,0) *v[0] + m.el(2,1) *v[1] + m.el(2,2) *v[2]);
		return o;
	}



	ostream& operator << (ostream& os, const IntVector& vec)
	{
		cout << "(" << vec[0] << "," << vec[1] << "," << vec[2] << ")";
		return os;
	}

	ostream& operator << (ostream& os, const VolPart& v)
	{
		v.print();
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