#include "puzzlepartshower.h"
#include "puzzlepart.h"
#include "glut.h"
#include "math.h"

using namespace Visualization;
using namespace Geometry;

namespace {
	void drawSquare(const FloatVector& shift, const FloatVector& v1,const FloatVector& v2,const FloatVector& v3,const FloatVector& v4,const FloatVector& n)
	{
		glBegin(GL_POLYGON);
    glNormal3f(  n[0], n[1], n[2]);
		glVertex3f(  shift[0] + v1[0], shift[1] + v1[1], shift[2] + v1[2]);
		glVertex3f(  shift[0] + v2[0], shift[1] + v2[1], shift[2] + v2[2]);
		glVertex3f(  shift[0] + v3[0], shift[1] + v3[1], shift[2] + v3[2]);
		glVertex3f(  shift[0] + v4[0], shift[1] + v4[1], shift[2] + v4[2]);
		glEnd();
	}
	void drawTriangle(const FloatVector& v1,const FloatVector& v2,const FloatVector& v3,const FloatVector& n)
	{
		glBegin(GL_TRIANGLES);
    glNormal3f(  n[0], n[1], n[2]);
		glVertex3f(  v1[0], v1[1], v1[2]);
		glVertex3f(  v2[0], v2[1], v2[2]);
		glVertex3f(  v3[0], v3[1], v3[2]);
		glEnd();
	}
  void drawTriangle(const FloatVector& shift, const FloatVector& v1,const FloatVector& v2,const FloatVector& v3,const FloatVector& n)
  {
    glBegin(GL_TRIANGLES);
    glNormal3f(  n[0], n[1], n[2]);
    glVertex3f(  shift[0] + v1[0], shift[1] + v1[1], shift[2] + v1[2]);
    glVertex3f(  shift[0] + v2[0], shift[1] + v2[1], shift[2] + v2[2]);
    glVertex3f(  shift[0] + v3[0], shift[1] + v3[1], shift[2] + v3[2]);
    glEnd();
  }
}

void PuzzlePartDrawer::draw(const PuzzlePart& part) const
{
	VolPartDrawer volPartDrawer;
	for (vector<VolPart>::const_iterator it = part.parts.cbegin(); it != part.parts.cend(); it++)
	{
		volPartDrawer.draw(*it);
	}
}

void VolPartDrawer::draw(const VolPart& v) const
{
  FloatVector verts[8];
  verts[0] = FloatVector(0,0,0);
  verts[1] = FloatVector(1,0,0);
  verts[2] = FloatVector(1,1,0);
  verts[3] = FloatVector(0,1,0);

  verts[4] = FloatVector(0,0,1);
  verts[5] = FloatVector(1,0,1);
  verts[6] = FloatVector(1,1,1);
  verts[7] = FloatVector(0,1,1);

	if (v.type() == VolPart::Empty) return;
	////////////////////////////////
	if (v.type() == VolPart::Full || dot(v.getDir(),FloatVector(1,0,0))>0)
	{
		drawSquare(v.getCoords(), verts[0], verts[3], verts[7], verts[4], FloatVector(-1.0, 0.0, 0.0));
	}
	if (v.type() == VolPart::Full || dot(v.getDir(),FloatVector(1,0,0))<0)
	{
		drawSquare(v.getCoords(), verts[1], verts[5], verts[6], verts[2], FloatVector(1.0, 0.0, 0.0));
	}
	////////////////////////////////
	if (v.type() == VolPart::Full || dot(v.getDir(),FloatVector(0,1,0))>0)
	{
		drawSquare(v.getCoords(), verts[0], verts[4], verts[5], verts[1], FloatVector(0.0, -1.0, 0.0));
	}
	if (v.type() == VolPart::Full || dot(v.getDir(),FloatVector(0,1,0))<0)
	{
		drawSquare(v.getCoords(), verts[3], verts[2], verts[6], verts[7], FloatVector(0.0, 1.0, 0.0));
	}
	////////////////////////////////
	if (v.type() == VolPart::Full || dot(v.getDir(),FloatVector(0,0,1))>0)
	{
		drawSquare(v.getCoords(), verts[0], verts[1], verts[2], verts[3], FloatVector(0.0, 0.0, -1.0));
	}
	if (v.type() == VolPart::Full || dot(v.getDir(),FloatVector(0,0,1))<0)
	{
		drawSquare(v.getCoords(), verts[4], verts[7], verts[6], verts[5], FloatVector(0.0, 0.0, 1.0));
	}
	if (v.type() == VolPart::Angle)
	{
		////////////////////////////////
		float s2 = sqrt(1/2.);
		const FloatVector& dir = v.getDir();
		if (dot(dir,FloatVector(1,1,0)) == 2)
		{
			drawSquare(v.getCoords(), verts[5], verts[7], verts[3], verts[1], FloatVector(s2, s2, 0.0));
			drawTriangle(v.getCoords() + FloatVector(1,0,0),v.getCoords() + FloatVector(0,0,0),v.getCoords() + FloatVector(0,1,0), FloatVector(0,0,-1));
			drawTriangle(v.getCoords() + FloatVector(1,0,1),v.getCoords() + FloatVector(0,1,1),v.getCoords() + FloatVector(0,0,1), FloatVector(0,0,1));
		}
		if (dot(dir,FloatVector(1,1,0)) == -2)
		{
			drawSquare(v.getCoords(), verts[1], verts[3], verts[7], verts[5], FloatVector(-s2, -s2, 0.0));
			drawTriangle(v.getCoords() + FloatVector(1,0,0),v.getCoords() + FloatVector(0,1,0),v.getCoords() + FloatVector(1,1,0), FloatVector(0,0,-1));
			drawTriangle(v.getCoords() + FloatVector(1,0,1),v.getCoords() + FloatVector(1,1,1),v.getCoords() + FloatVector(0,1,1), FloatVector(0,0,1));
		}
		if (dir[0] == 1 && dir[1] == -1) 
		{
			drawSquare(v.getCoords(), verts[4], verts[6], verts[2], verts[0], FloatVector(s2, -s2, 0.0));
			drawTriangle(v.getCoords() + FloatVector(0,0,0),v.getCoords() + FloatVector(0,1,0),v.getCoords() + FloatVector(1,1,0), FloatVector(0,0,-1));
			drawTriangle(v.getCoords() + FloatVector(0,0,1),v.getCoords() + FloatVector(1,1,1),v.getCoords() + FloatVector(0,1,1), FloatVector(0,0,1));
		}
		if (dir[0] == -1 && dir[1] == 1)
		{
			drawSquare(v.getCoords(), verts[0], verts[2], verts[6], verts[4], FloatVector(-s2, s2, 0.0));
			drawTriangle(v.getCoords() + FloatVector(0,0,0),v.getCoords() + FloatVector(1,1,0),v.getCoords() + FloatVector(1,0,0),FloatVector(0,0,-1));
			drawTriangle(v.getCoords() + FloatVector(0,0,1),v.getCoords() + FloatVector(1,0,1),v.getCoords() + FloatVector(1,1,1),FloatVector(0,0,1));
		}
		////////////////////////////////
		if (dot(dir,FloatVector(1,0,1)) == 2)
		{
			drawSquare(v.getCoords(), verts[4], verts[7], verts[2], verts[1], FloatVector(s2, 0.0, s2));
			drawTriangle(v.getCoords() + FloatVector(0,0,1),v.getCoords() + FloatVector(0,0,0),v.getCoords() + FloatVector(1,0,0), FloatVector(0,-1,0));
			drawTriangle(v.getCoords() + FloatVector(0,1,1),v.getCoords() + FloatVector(1,1,0),v.getCoords() + FloatVector(0,1,0), FloatVector(0,1,0));
		}
		if (dot(dir,FloatVector(1,0,1)) == -2)
		{
			drawSquare(v.getCoords(), verts[1], verts[2], verts[7], verts[4], FloatVector(-s2, 0.0, -s2));
			drawTriangle(v.getCoords() + FloatVector(1,0,0),v.getCoords() + FloatVector(1,0,1),v.getCoords() + FloatVector(0,0,1),FloatVector(0,-1,0));
			drawTriangle(v.getCoords() + FloatVector(1,1,0),v.getCoords() + FloatVector(0,1,1),v.getCoords() + FloatVector(1,1,1),FloatVector(0,1,0));
		}
		if (dir[0] == 1 && dir[2] == -1) 
		{
			drawSquare(v.getCoords(), verts[0], verts[5], verts[6], verts[3], FloatVector(s2, 0.0, -s2));
			drawTriangle(v.getCoords() + FloatVector(1,0,1),v.getCoords() + FloatVector(0,0,1),v.getCoords() + FloatVector(0,0,0), FloatVector(0,-1,0));
			drawTriangle(v.getCoords() + FloatVector(1,1,1),v.getCoords() + FloatVector(0,1,0),v.getCoords() + FloatVector(0,1,1), FloatVector(0,1,0));
		}
		if (dir[0] == -1 && dir[2] == 1)
		{
			drawSquare(v.getCoords(), verts[3], verts[6], verts[5], verts[0], FloatVector(-s2, 0.0, s2));
			drawTriangle(v.getCoords() + FloatVector(1,0,0),v.getCoords() + FloatVector(1,0,1),v.getCoords() + FloatVector(0,0,0), FloatVector(0,-1,0));
			drawTriangle(v.getCoords() + FloatVector(1,1,0),v.getCoords() + FloatVector(0,1,0),v.getCoords() + FloatVector(1,1,1), FloatVector(0,1,0));
		}
		////////////////////////////////
		if (dot(dir,FloatVector(0,1,1)) == 2)
		{
			drawSquare(v.getCoords(), verts[3], verts[2], verts[5], verts[4], FloatVector(0.0, s2, s2));
			drawTriangle(v.getCoords() + FloatVector(0,0,0),v.getCoords() + FloatVector(0,0,1),v.getCoords() + FloatVector(0,1,0), FloatVector(-1,0,0));
			drawTriangle(v.getCoords() + FloatVector(1,0,0),v.getCoords() + FloatVector(1,1,0),v.getCoords() + FloatVector(1,0,1), FloatVector(1,0,0));
		}
		if (dot(dir,FloatVector(0,1,1)) == -2)
		{
			drawSquare(v.getCoords(), verts[4], verts[5], verts[2], verts[3], FloatVector(0.0, -s2, -s2));
			drawTriangle(v.getCoords() + FloatVector(0,0,1),v.getCoords() + FloatVector(0,1,1),v.getCoords() + FloatVector(0,1,0), FloatVector(-1,0,0));
			drawTriangle(v.getCoords() + FloatVector(1,0,1),v.getCoords() + FloatVector(1,1,0),v.getCoords() + FloatVector(1,1,1), FloatVector(1,0,0));
		}
		if (dir[1] == 1 && dir[2] == -1) 
		{
			drawSquare(v.getCoords(), verts[1], verts[6], verts[7], verts[0], FloatVector(0.0, s2, -s2));
			drawTriangle(v.getCoords() + FloatVector(0,0,0),v.getCoords() + FloatVector(0,0,1),v.getCoords() + FloatVector(0,1,1), FloatVector(-1,0,0));
			drawTriangle(v.getCoords() + FloatVector(1,0,0),v.getCoords() + FloatVector(1,1,1),v.getCoords() + FloatVector(1,0,1), FloatVector(1,0,0));
		}
		if (dir[1] == -1 && dir[2] == 1)
		{
			drawSquare(v.getCoords(), verts[0], verts[7], verts[6], verts[1], FloatVector(0.0, -s2, s2));
			drawTriangle(v.getCoords() + FloatVector(0,0,0),v.getCoords() + FloatVector(0,1,1),v.getCoords() + FloatVector(0,1,0), FloatVector(-1,0,0));
			drawTriangle(v.getCoords() + FloatVector(1,0,0),v.getCoords() + FloatVector(1,1,0),v.getCoords() + FloatVector(1,1,1), FloatVector(1,0,0));
		}
	}
}
bool VolPartDrawer::couldDraw_(const Geometry::VolPart& v, Triangle tri) const
{
	if (v.type() != VolPart::Angle) return true;

	if (v.getDir()[0] == 0)
	{
		return triIntersectsPlane_(tri, Plane(v.getCoords() + FloatVector(0.5,0.5,0.5), FloatVector(0,1,1)));
	}
	else if (v.getDir()[1] == 0)
	{
		return triIntersectsPlane_(tri, Plane(v.getCoords() + FloatVector(0.5,0.5,0.5), FloatVector(1,0,1)));
	}
	else
	{
		return triIntersectsPlane_(tri, Plane(v.getCoords() + FloatVector(0.5,0.5,0.5), FloatVector(1,1,0)));
	}
}
bool VolPartDrawer::triIntersectsPlane_(Triangle tri, Plane p) const
{
	return !(dot(tri.n,p.p - tri.v1) >=0 && dot(tri.n,p.p - tri.v2) >=0 && dot(tri.n,p.p - tri.v3) >=0 || dot(tri.n,p.p - tri.v1) <=0 && dot(tri.n,p.p - tri.v2) <=0 && dot(tri.n,p.p - tri.v3) <=0);
}

