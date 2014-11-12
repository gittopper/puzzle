#include "pieceshower.h"
#include "glrenderer.h"
#include "print.h"
#include "GL/gl.h"
#include "GL/glu.h"
#include <cstdlib>
#include <time.h>

using namespace Visualization;
using namespace Geometry;


void GLRenderer::initOpenGL()
{
  glFrontFace(GL_CCW);
  //glMatrixMode(GL_PROJECTION);
  glEnable(GL_COLOR_MATERIAL);
  glClearColor(0.5, 0.5, 0.5, 1.0);
  glEnable(GL_LIGHTING);
  glEnable(GL_DEPTH_TEST);

  GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
  glEnable(GL_LIGHT0);


  GLfloat pos[] = { 1.0, 0.0, 5.0, 0.0 };
  glLightfv(GL_LIGHT0, GL_POSITION, pos);

  glShadeModel(GL_SMOOTH);
  glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

  zoom = 7;
  rotate_y = 45;
  rotate_x = 45;

  srand(time(NULL));

  curSol = 0;
  maxSol = 0;
}

void GLRenderer::showSolution(int sol)
{
  curSol = sol;
}

void GLRenderer::display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glPushMatrix();
  glRotatef(rotate_x, 1.0, 0.0, 0.0);
  glRotatef(rotate_y, 0.0, 1.0, 0.0);

  drawLCS();

  glColor3f(0.2, 0.0, 0.0);

  PiecesSetShower drawer;
  PiecesSet sol;
  int ns = puzzle->numFoundSolutions();
  int i = curSol>0 ? curSol : ns;
  puzzle->getSolution(sol, i);
  sol.shift(Vector(-5/2.,-6/2., -4/2.));

  if (ns > maxSol)
  {
    for (int is = maxSol + 1; is <= ns; is++)
    {
      addMenuEntry(is);
    }
    maxSol = ns;
  }

  //drawer.draw(sol);

  PieceDrawer partDrawer;

  Vector cm;
  for (int i = 0; i < sol.pieces.size(); i++)
  {
    cm += sol.pieces[i].getZero();
  }
  cm = cm * (1. / sol.pieces.size());

  for (int i = 0; i < sol.pieces.size(); i++)
  {
    Piece p = sol.pieces[i];
    if (colors.size() <= i)
    {
      colors.push_back(Vector((rand() % 256) / 256., (rand() % 256) / 256., (rand() % 256) / 256.));
    }

    glColor3f(colors[i][0], colors[i][1], colors[i][2]);
    //p.shift(-cm + (sol.pieces[i].getZero() - cm)*0.2);
    p.shift(-cm);
    partDrawer.draw(p);
  }

  glPopMatrix();

  glFlush();
}

void GLRenderer::resize(int width, int height)
{
  w = width;
  h = height;

  float l = zoom;

  glViewport(0, 0, (GLsizei)w, (GLsizei)h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (w <= h)
    glOrtho(-l, l, -l*(GLfloat)h / (GLfloat)w,
    l*(GLfloat)h / (GLfloat)w, -l, l);

  else
    glOrtho(-l*(GLfloat)w / (GLfloat)h,
    l*(GLfloat)w / (GLfloat)h, -l, l, -l, l);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}


void GLRenderer::drawLCS()
{
  glLineWidth(2.0);
  glColor3f(1.0, 0.0, 0.0);
  glBegin(GL_LINES);
  glVertex3f(0.0, 0.0, 0.0);
  glVertex3f(2., 0, 0);
  glEnd();

  glColor3f(0.0, 1.0, 0.0);
  glBegin(GL_LINES);
  glVertex3f(0.0, 0.0, 0.0);
  glVertex3f(0., 2, 0);
  glEnd();

  glColor3f(0.0, 0.0, 1.0);
  glBegin(GL_LINES);
  glVertex3f(0.0, 0.0, 0.0);
  glVertex3f(0., 0, 2);
  glEnd();
}

void GLRenderer::setPuzzleToRender(VolumePuzzle& puzzleToRender)
{
  puzzle = &puzzleToRender;
}

void GLRenderer::mouseLButtonDown(int x, int y)
{
  rx0 = rotate_x;
  ry0 = rotate_y;

  xm = x;
  ym = y;
}

void GLRenderer::mouseLButtonUp(int x, int y)
{

}

void GLRenderer::mouseRButtonDown(int x, int y)
{
  rx0 = rotate_x;
  ry0 = rotate_y;

  xm = x;
  ym = y;
}

void GLRenderer::mouseMove(int x, int y)
{
  rotate_x = rx0 - 180. * float(ym - y) / h;
  rotate_y = ry0 - 180. * float(xm - x) / w;
}

void GLRenderer::mouseRButtonUp(int x, int y)
{

}

void GLRenderer::wheelUp(int x, int y)
{
  zoom++;
  resize(w, h);
}

void GLRenderer::wheelDown(int x, int y)
{
  zoom--;
  resize(w, h);
}

void GLRenderer::rotateX(float x)
{
  rotate_x += x;
}

void GLRenderer::rotateY(float y)
{
  rotate_y += y;
}
