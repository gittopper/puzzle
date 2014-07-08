#pragma once
#include "intvector.h"

namespace Geometry
{
	class Mat
	{
	public:
		Mat(){}
		Mat(IntVector v1,IntVector v2, IntVector v3);
		const double el(int i, int j) const
		{
			return ar[i*3 + j];
		}
		double& el(int i, int j)
		{
			return ar[i*3 + j];
		}
		double det()const;
		void scale(double val);
		Mat inverse();
		bool operator == (const Mat& m) const;
		Mat operator * (const Mat& m) const;
		IntVector operator * (const IntVector& v) const;
	private:
		double ar[9];
	};
}