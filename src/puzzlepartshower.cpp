#include "puzzlepartshower.h"
#include "puzzlepart.h"
#include "glut.h"
#include "math.h"

using namespace Visualization;
using namespace Geometry;

namespace {
	void drawSquare(const IntVector& v1,const IntVector& v2,const IntVector& v3,const IntVector& v4)
	{
		glVertex3f(  v1[0], v1[1], v1[2]);
		glVertex3f(  v2[0], v2[1], v2[2]);
		glVertex3f(  v3[0], v3[1], v3[2]);
		glVertex3f(  v4[0], v4[1], v4[2]);
	}
	void drawTriangle(const IntVector& v1,const IntVector& v2,const IntVector& v3,const IntVector& n)
	{
		glBegin(GL_TRIANGLES);
		glVertex3f(  v1[0], v1[1], v1[2]);
		glVertex3f(  v2[0], v2[1], v2[2]);
		glVertex3f(  v3[0], v3[1], v3[2]);
		glNormal3f(  n[0], n[1], n[2]);
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
	if (v.type() == VolPart::Empty) return;
	////////////////////////////////
	if (v.type() == VolPart::Full || dot(v.getDir(),IntVector(1,0,0))>0)
	{
		glBegin(GL_POLYGON);
		drawSquare(v.getCoords(),v.getCoords() + IntVector(0,0,1),v.getCoords() + IntVector(0,1,1),v.getCoords() + IntVector(0,1,0));
		glNormal3f(-1.0, 0.0, 0.0);
		glEnd();
	}
	if (v.type() == VolPart::Full || dot(v.getDir(),IntVector(1,0,0))<0)
	{
		glBegin(GL_POLYGON);
		drawSquare(v.getCoords() + IntVector(1,0,0),v.getCoords() + IntVector(1,1,0),v.getCoords() + IntVector(1,1,1),v.getCoords() + IntVector(1,0,1));
		glNormal3f(1.0, 0.0, 0.0);
		glEnd();
	}
	////////////////////////////////
	if (v.type() == VolPart::Full || dot(v.getDir(),IntVector(0,1,0))>0)
	{
		glBegin(GL_POLYGON);
		drawSquare(v.getCoords(),v.getCoords() + IntVector(1,0,0),v.getCoords() + IntVector(1,0,1),v.getCoords() + IntVector(0,0,1));
		glNormal3f(0.0, -1.0, 0.0);
		glEnd();
	}
	if (v.type() == VolPart::Full || dot(v.getDir(),IntVector(0,1,0))<0)
	{
		glBegin(GL_POLYGON);
		drawSquare(v.getCoords() + IntVector(0,1,0),v.getCoords() + IntVector(0,1,1),v.getCoords() + IntVector(1,1,1),v.getCoords() + IntVector(1,1,0));
		glNormal3f(0.0, 1.0, 0.0);
		glEnd();
	}
	////////////////////////////////
	if (v.type() == VolPart::Full || dot(v.getDir(),IntVector(0,0,1))>0)
	{
		glBegin(GL_POLYGON);
		drawSquare(v.getCoords(),v.getCoords() + IntVector(0,1,0),v.getCoords() + IntVector(1,1,0),v.getCoords() + IntVector(1,0,0));
		glNormal3f(0.0, 0.0, -1.0);
		glEnd();
	}
	if (v.type() == VolPart::Full || dot(v.getDir(),IntVector(0,0,1))<0)
	{
		glBegin(GL_POLYGON);
		drawSquare(v.getCoords() + IntVector(0,0,1),v.getCoords() + IntVector(0,1,1),v.getCoords() + IntVector(1,1,1),v.getCoords() + IntVector(1,0,1));
		glNormal3f(0.0, 0.0, 1.0);
		glEnd();
	}
	if (v.type() == VolPart::Angle)
	{
		////////////////////////////////
		float s2 = sqrt(1/2.);
		const IntVector& dir = v.getDir();
		if (dot(dir,IntVector(1,1,0)) == 2)
		{
			glBegin(GL_POLYGON);
			drawSquare(v.getCoords() + IntVector(1,0,1),v.getCoords() + IntVector(1,0,0),v.getCoords() + IntVector(0,1,0),v.getCoords() + IntVector(0,1,1));
			glNormal3f(s2, s2, 0.0);
			glEnd();
			drawTriangle(v.getCoords() + IntVector(1,0,0),v.getCoords() + IntVector(0,0,0),v.getCoords() + IntVector(0,1,0),v.getCoords() + IntVector(0,0,-1));
			drawTriangle(v.getCoords() + IntVector(1,0,1),v.getCoords() + IntVector(0,1,1),v.getCoords() + IntVector(0,0,1),v.getCoords() + IntVector(0,0,1));
		}
		if (dot(dir,IntVector(1,1,0)) == -2)
		{
			glBegin(GL_POLYGON);
			drawSquare(v.getCoords() + IntVector(1,0,0),v.getCoords() + IntVector(1,0,1),v.getCoords() + IntVector(0,1,1),v.getCoords() + IntVector(0,1,0));
			glNormal3f(-s2, -s2, 0.0);
			glEnd();
			drawTriangle(v.getCoords() + IntVector(1,0,0),v.getCoords() + IntVector(0,1,0),v.getCoords() + IntVector(1,1,0),v.getCoords() + IntVector(0,0,-1));
			drawTriangle(v.getCoords() + IntVector(1,0,1),v.getCoords() + IntVector(1,1,1),v.getCoords() + IntVector(0,1,1),v.getCoords() + IntVector(0,0,1));
		}
		if (dir[0] == 1 && dir[1] == -1) 
		{
			glBegin(GL_POLYGON);
			drawSquare(v.getCoords() + IntVector(1,1,0),v.getCoords() + IntVector(1,1,1),v.getCoords() + IntVector(0,0,1),v.getCoords() + IntVector(0,0,0));
			glNormal3f(s2, -s2, 0.0);
			glEnd();
			drawTriangle(v.getCoords() + IntVector(0,0,0),v.getCoords() + IntVector(0,1,0),v.getCoords() + IntVector(1,1,0),v.getCoords() + IntVector(0,0,-1));
			drawTriangle(v.getCoords() + IntVector(0,0,1),v.getCoords() + IntVector(1,1,1),v.getCoords() + IntVector(0,1,1),v.getCoords() + IntVector(0,0,1));
		}
		if (dir[0] == -1 && dir[1] == 1)
		{
			glBegin(GL_POLYGON);
			drawSquare(v.getCoords() + IntVector(0,0,0),v.getCoords() + IntVector(0,0,1),v.getCoords() + IntVector(1,1,1),v.getCoords() + IntVector(1,1,0));
			glNormal3f(-s2, s2, 0.0);
			glEnd();
			drawTriangle(v.getCoords() + IntVector(0,0,0),v.getCoords() + IntVector(1,1,0),v.getCoords() + IntVector(1,0,0),v.getCoords() + IntVector(0,0,-1));
			drawTriangle(v.getCoords() + IntVector(0,0,1),v.getCoords() + IntVector(1,0,1),v.getCoords() + IntVector(1,1,1),v.getCoords() + IntVector(0,0,1));
		}
		////////////////////////////////
		if (dot(dir,IntVector(1,0,1)) == 2)
		{
			glBegin(GL_POLYGON);
			drawSquare(v.getCoords() + IntVector(0,1,1),v.getCoords() + IntVector(0,0,1),v.getCoords() + IntVector(1,0,0),v.getCoords() + IntVector(1,1,0));
			glNormal3f(s2, 0.0, s2);
			glEnd();
			drawTriangle(v.getCoords() + IntVector(0,0,1),v.getCoords() + IntVector(0,0,0),v.getCoords() + IntVector(1,0,0),v.getCoords() + IntVector(0,-1,0));
			drawTriangle(v.getCoords() + IntVector(0,1,1),v.getCoords() + IntVector(1,1,0),v.getCoords() + IntVector(0,1,0),v.getCoords() + IntVector(0,1,0));
		}
		if (dot(dir,IntVector(1,0,1)) == -2)
		{
			glBegin(GL_POLYGON);
			drawSquare(v.getCoords() + IntVector(0,0,1),v.getCoords() + IntVector(0,1,1),v.getCoords() + IntVector(1,1,0),v.getCoords() + IntVector(1,0,0));
			glNormal3f(-s2, 0.0, -s2);
			glEnd();
			drawTriangle(v.getCoords() + IntVector(1,0,0),v.getCoords() + IntVector(1,0,1),v.getCoords() + IntVector(0,0,1),v.getCoords() + IntVector(0,-1,0));
			drawTriangle(v.getCoords() + IntVector(1,1,0),v.getCoords() + IntVector(0,1,1),v.getCoords() + IntVector(1,1,1),v.getCoords() + IntVector(0,1,0));
		}
		if (dir[0] == 1 && dir[2] == -1) 
		{
			glBegin(GL_POLYGON);
			drawSquare(v.getCoords() + IntVector(1,0,1),v.getCoords() + IntVector(0,0,0),v.getCoords() + IntVector(0,1,0),v.getCoords() + IntVector(1,1,1));
			glNormal3f(s2, 0.0, -s2);
			glEnd();
			drawTriangle(v.getCoords() + IntVector(1,0,1),v.getCoords() + IntVector(0,0,1),v.getCoords() + IntVector(0,0,0),v.getCoords() + IntVector(0,-1,0));
			drawTriangle(v.getCoords() + IntVector(1,1,1),v.getCoords() + IntVector(0,1,0),v.getCoords() + IntVector(0,1,1),v.getCoords() + IntVector(0,1,0));
		}
		if (dir[0] == -1 && dir[2] == 1)
		{
			glBegin(GL_POLYGON);
			drawSquare(v.getCoords() + IntVector(1,0,1),v.getCoords() + IntVector(1,1,1),v.getCoords() + IntVector(0,1,0),v.getCoords() + IntVector(0,0,0));
			glNormal3f(-s2, 0.0, s2);
			glEnd();
			drawTriangle(v.getCoords() + IntVector(1,0,0),v.getCoords() + IntVector(1,0,1),v.getCoords() + IntVector(0,0,0),v.getCoords() + IntVector(0,-1,0));
			drawTriangle(v.getCoords() + IntVector(1,1,0),v.getCoords() + IntVector(0,1,0),v.getCoords() + IntVector(1,1,1),v.getCoords() + IntVector(0,1,0));
		}
		////////////////////////////////
		if (dot(dir,IntVector(0,1,1)) == 2)
		{
			glBegin(GL_POLYGON);
			drawSquare(v.getCoords() + IntVector(0,1,0),v.getCoords() + IntVector(0,0,1),v.getCoords() + IntVector(1,0,1),v.getCoords() + IntVector(1,1,0));
			glNormal3f(0.0, s2, s2);
			glEnd();
			drawTriangle(v.getCoords() + IntVector(0,0,0),v.getCoords() + IntVector(0,0,1),v.getCoords() + IntVector(0,1,0),v.getCoords() + IntVector(-1,0,0));
			drawTriangle(v.getCoords() + IntVector(1,0,0),v.getCoords() + IntVector(1,1,0),v.getCoords() + IntVector(1,0,1),v.getCoords() + IntVector(1,0,0));
		}
		if (dot(dir,IntVector(0,1,1)) == -2)
		{
			glBegin(GL_POLYGON);
			drawSquare(v.getCoords() + IntVector(1,1,0),v.getCoords() + IntVector(1,0,1),v.getCoords() + IntVector(0,0,1),v.getCoords() + IntVector(0,1,0));
			glNormal3f(0.0, -s2, -s2);
			glEnd();
			drawTriangle(v.getCoords() + IntVector(0,0,1),v.getCoords() + IntVector(0,1,1),v.getCoords() + IntVector(0,1,0),v.getCoords() + IntVector(-1,0,0));
			drawTriangle(v.getCoords() + IntVector(1,0,1),v.getCoords() + IntVector(1,1,0),v.getCoords() + IntVector(1,1,1),v.getCoords() + IntVector(1,0,0));
		}
		if (dir[1] == 1 && dir[2] == -1) 
		{
			glBegin(GL_POLYGON);
			drawSquare(v.getCoords() + IntVector(0,1,1),v.getCoords() + IntVector(1,1,1),v.getCoords() + IntVector(1,0,0),v.getCoords() + IntVector(0,0,0));
			glNormal3f(0.0, s2, -s2);
			glEnd();
			drawTriangle(v.getCoords() + IntVector(0,0,0),v.getCoords() + IntVector(0,0,1),v.getCoords() + IntVector(0,1,1),v.getCoords() + IntVector(-1,0,0));
			drawTriangle(v.getCoords() + IntVector(1,0,0),v.getCoords() + IntVector(1,1,1),v.getCoords() + IntVector(1,0,1),v.getCoords() + IntVector(1,0,0));
		}
		if (dir[1] == -1 && dir[2] == 1)
		{
			glBegin(GL_POLYGON);
			drawSquare(v.getCoords() + IntVector(1,0,0),v.getCoords() + IntVector(1,1,1),v.getCoords() + IntVector(0,1,1),v.getCoords() + IntVector(0,0,0));
			glNormal3f(0.0, -s2, s2);
			glEnd();
			drawTriangle(v.getCoords() + IntVector(0,0,0),v.getCoords() + IntVector(0,1,1),v.getCoords() + IntVector(0,1,0),v.getCoords() + IntVector(-1,0,0));
			drawTriangle(v.getCoords() + IntVector(1,0,0),v.getCoords() + IntVector(1,1,0),v.getCoords() + IntVector(1,1,1),v.getCoords() + IntVector(1,0,0));
		}
	}
}
bool VolPartDrawer::couldDraw_(const Geometry::VolPart& v, Triangle tri) const
{
	if (v.type() != VolPart::Angle) return true;

	if (v.getDir()[0] == 0)
	{
		return triIntersectsPlane_(tri, Plane(v.getCoords() + IntVector(0.5,0.5,0.5), IntVector(0,1,1)));
	}
	else if (v.getDir()[1] == 0)
	{
		return triIntersectsPlane_(tri, Plane(v.getCoords() + IntVector(0.5,0.5,0.5), IntVector(1,0,1)));
	}
	else
	{
		return triIntersectsPlane_(tri, Plane(v.getCoords() + IntVector(0.5,0.5,0.5), IntVector(1,1,0)));
	}
}
bool VolPartDrawer::triIntersectsPlane_(Triangle tri, Plane p) const
{
	return !(dot(tri.n,p.p - tri.v1) >=0 && dot(tri.n,p.p - tri.v2) >=0 && dot(tri.n,p.p - tri.v3) >=0 || dot(tri.n,p.p - tri.v1) <=0 && dot(tri.n,p.p - tri.v2) <=0 && dot(tri.n,p.p - tri.v3) <=0);
}

