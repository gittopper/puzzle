#pragma once
#include "intvector.h"

namespace Geometry
{
	class PuzzlePart;
	class VolPart;
  class PuzzlesSet;
}

namespace Visualization
{

	class PuzzlePartDrawer
	{
	public:
		void draw(const Geometry::PuzzlePart& part) const;
	};

  class PuzzlesSetDrawer
  {
  public:
    void draw(const Geometry::PuzzlesSet& puzzles) const;
  private:
    PuzzlePartDrawer partDrawer;
  };

	class VolPartDrawer
	{
	public:
		void draw(const Geometry::VolPart& v) const;
	private:
		class Triangle
		{
		public:
			Triangle(Geometry::FloatVector vert1, Geometry::FloatVector vert2,Geometry::FloatVector vert3, Geometry::FloatVector ni):v1(vert1),v2(vert2),v3(vert3),n(ni){}
			Geometry::FloatVector v1,v2,v3,n;
		};
		class Plane
		{
		public:
			Plane(Geometry::FloatVector pi, Geometry::FloatVector ni):p(pi),n(ni){}
			Geometry::FloatVector p,n;
		};
		bool couldDraw_(const Geometry::VolPart& v, Triangle tri) const;
		bool triIntersectsPlane_(Triangle tri, Plane p) const;
	};
}
