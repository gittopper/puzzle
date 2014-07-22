#include "puzzlepartshower.h"
#include "visualization.h"
#include <glut.h>
#include "utils.h"
#include "solver.h"
#include "print.h"

using namespace Visualization;
using namespace Geometry;

double rotate_y=45; 
double rotate_x=45;


bool makeGeneralTests()
{
  BREAK_ON_LINE(FloatVector(0,0,1).rotate(RotateX) == FloatVector(0,1,0));
  BREAK_ON_LINE(FloatVector(0,0,1).rotate(RotateX).rotate(RotateX) == FloatVector(0,0,-1));

  BREAK_ON_LINE(FloatVector(1,0,0).rotate(RotateY) == FloatVector(0,0,1));
  BREAK_ON_LINE(FloatVector(1,0,0).rotate(RotateY).rotate(RotateY) == FloatVector(-1,0,0));

  BREAK_ON_LINE(FloatVector(0,1,0).rotate(RotateZ) == FloatVector(1,0,0));
  BREAK_ON_LINE(FloatVector(0,1,0).rotate(RotateZ).rotate(RotateZ) == FloatVector(0,-1,0));


  PuzzlesSet puzzles = generateWoodPuzzles();
  PuzzlePart part = puzzles[0];
  part.rotate(RotateX);
  part.centralize();

  PuzzlePart p1(1);
  p1.parts.push_back(VolPart(VolPart::Full,FloatVector(0,0,1)));
  p1.parts.push_back(VolPart(VolPart::Full,FloatVector(0,1,0)));
  p1.parts.push_back(VolPart(VolPart::Angle,FloatVector(0,0,0),FloatVector(1,0,-1)));
  p1.parts.push_back(VolPart(VolPart::Angle,FloatVector(0,1,1),FloatVector(0,1,1)));

  bool areEqual = part == p1;
  BREAK_ON_LINE(areEqual);

  Mat m(FloatVector(0,-1,0),FloatVector(0,0,1),FloatVector(1,0,0));

  Mat rotX(1,0,0, 0,0,-1, 0,1,0);
  Mat rotZ(0,-1,0, 1,0,0, 0,0,1);

  PuzzlesSet rotatedPuzzles = puzzles;
  rotatedPuzzles.rotate(rotX);
  BREAK_ON_LINE(rotatedPuzzles==puzzles);
  rotatedPuzzles.rotate(rotZ);
  BREAK_ON_LINE(rotatedPuzzles==puzzles);

  Mat r = m * m.inverse();
  Mat e(FloatVector(1,0,0),FloatVector(0,1,0),FloatVector(0,0,1));
  BREAK_ON_LINE(r == e);
  FloatVector v = e * FloatVector(-1,1,2);
  BREAK_ON_LINE(v == FloatVector(-1,1,2));
  return true;
}

void solvePuzzle()
{
  BREAK_ON_LINE(makeGeneralTests());
  //   Solver testSolver(2,2,2,generateTestPuzzles());

  PuzzlesSet puzzles = generateWoodPuzzles();
  Solver solver(3,4,2,puzzles);
  cout << puzzles;
  solver.solve();

  //   Solver somaSolver(3,3,3,generateSomaPuzzles());
  //   somaSolver.solve();

  cout << "Press any key to exit..."<<flush;
  cin.get();
}

void Display() {
  glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glShadeModel(GL_SMOOTH);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	glLoadIdentity();

	float l = 15;
	//glOrtho(-l, l, -l, l, -l, l);
  glOrtho(-3, l, -3, l, -l, l);


	GLfloat pos[]={5.0, 0.0, 5.0, 0.0};
	glLightfv(GL_LIGHT0, GL_POSITION, pos);

	glPushMatrix();
	glRotatef( rotate_x, 1.0, 0.0, 0.0 );
	glRotatef( rotate_y, 0.0, 1.0, 0.0 );

	glLineWidth(2.0); 
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(2., 0, 0);
	glEnd();

	glLineWidth(2.0); 
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0., 2, 0);
	glEnd();

	glLineWidth(2.0); 
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0., 0, 2);
	glEnd();

	glColor3f(   0.2,  0.0, 0.0 );
	PuzzlePartDrawer drawer;
	PuzzlesSet puzzles = generateWoodPuzzles();

	for (int i = 0; i < puzzles.size(); i++)
	{
		PuzzlePart p = puzzles[i];
		p.shift(FloatVector(i*3));
		drawer.draw(p);
	}
//  solvePuzzle();

	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

void Initialize() {
	glFrontFace(GL_CCW);
	//glMatrixMode(GL_PROJECTION);
	glEnable(GL_COLOR_MATERIAL);
	glClearColor(0.5,0.5,0.5,1.0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST); 
	GLfloat diffuse[]={1.0, 1.0, 1.0, 1.0};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glEnable(GL_LIGHT0);
}

void specialKeys( int key, int x, int y ) {

	//  Right arrow - increase rotation by 5 degree
	if (key == GLUT_KEY_RIGHT)
		rotate_y += 5;

	//  Left arrow - decrease rotation by 5 degree
	else if (key == GLUT_KEY_LEFT)
		rotate_y -= 5;

	else if (key == GLUT_KEY_UP)
		rotate_x += 5;

	else if (key == GLUT_KEY_DOWN)
		rotate_x -= 5;

	//  Request display update
	glutPostRedisplay();

}
int realMain(int argc, char ** argv) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 200);
	glutCreateWindow("Puzzle visualizer");
	glutDisplayFunc(Display);
	glutSpecialFunc(specialKeys);
	Initialize();
	glutMainLoop();
	return 0;
}

