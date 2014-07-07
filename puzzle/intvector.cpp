#include "intvector.h"

namespace Geometry
{
	int dot(const IntVector& v1, const IntVector& v2)
	{
		return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
	}

	IntVector::IntVector(int i = 0, int j = 0, int k = 0)
	{
		vec[0] = i;
		vec[1] = j;
		vec[2] = k;
	}

	IntVector IntVector::cross(const IntVector v)
	{
		IntVector r;
		r[0] = vec[1] * v.vec[2] - vec[2] * v.vec[1];
		r[1] = vec[2] * v.vec[0] - vec[0] * v.vec[2];
		r[2] = vec[0] * v.vec[1] - vec[1] * v.vec[0];
		return r;
	}
	IntVector& IntVector::rotate(RotType rotation)
	{
		int x = vec[0];
		int y = vec[1];
		int z = vec[2];

		switch(rotation)
		{
		case RotateX:
			vec[1] = z;
			vec[2] = -y;
			break;
		case RotateY:
			vec[0] = -z;
			vec[2] = x;
			break;
		case RotateZ:
			vec[0] = y;
			vec[1] = -x;
		};
		return *this;
	}
	IntVector IntVector::operator-(const IntVector& v) const
	{
		return IntVector(vec[0] - v[0], vec[1] - v[1], vec[2] - v[2]);
	}
	bool IntVector::operator==(const IntVector& v) const
	{
		return vec[0] == v[0] && vec[1] == v[1] && vec[2] == v[2];
	}
	IntVector IntVector::operator-() const
	{
		return IntVector(-vec[0], -vec[1], -vec[2]);
	}
	IntVector IntVector::operator+(const IntVector& v) const
	{
		return IntVector(vec[0] + v[0], vec[1] + v[1], vec[2] + v[2]);
	}
}
