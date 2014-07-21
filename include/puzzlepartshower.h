#pragma once
#include "intvector.h"

namespace Geometry
{
	class PuzzlePart;
	class VolPart;
}

namespace Visualization
{

	class PuzzlePartDrawer
	{
	public:
		void draw(const Geometry::PuzzlePart& part) const;
	};

	class VolPartDrawer
	{
	public:
		void draw(const Geometry::VolPart& v) const;
	private:
		class Triangle
		{
		public:
			Triangle(Geometry::IntVector vert1, Geometry::IntVector vert2,Geometry::IntVector vert3, Geometry::IntVector ni):v1(vert1),v2(vert2),v3(vert3),n(ni){}
			Geometry::IntVector v1,v2,v3,n;
		};
		class Plane
		{
		public:
			Plane(Geometry::IntVector pi, Geometry::IntVector ni):p(pi),n(ni){}
			Geometry::IntVector p,n;
		};
		bool couldDraw_(const Geometry::VolPart& v, Triangle tri) const;
		bool triIntersectsPlane_(Triangle tri, Plane p) const;
	};
}
