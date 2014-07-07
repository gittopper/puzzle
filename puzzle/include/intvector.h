#include "base.h"

namespace Geometry
{
	enum RotType
	{
		None,
		RotateX,
		RotateY,
		RotateZ
	};

	class IntVector
	{
	public:
		IntVector(int i = 0, int j = 0, int k = 0);

		IntVector cross(const IntVector v);

		IntVector& rotate(RotType rotation);

		const int& IntVector::operator[](int i) const
		{
			return vec[i];
		}

		int& IntVector::operator[](int i)
		{
			return vec[i];
		}

		IntVector operator-(const IntVector& v) const;

		bool operator==(const IntVector& v) const;

		IntVector operator-() const;

		IntVector operator+(const IntVector& v) const;

	private:
		int vec[3];
	};


	int dot(const IntVector& v1, const IntVector& v2);
}
