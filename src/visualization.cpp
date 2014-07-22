#include "puzzlepartshower.h"
#include "visualization.h"
#include <glut.h>
#include "utils.h"

using namespace Visualization;
using namespace Geometry;

double rotate_y=0; 
double rotate_x=0;

void Display() {
  glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glShadeModel(GL_SMOOTH);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	glLoadIdentity();

	float l = 10;
	glOrtho(-l, l, -l, l, -l, l);


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
  PuzzlePart p2(2);
  p2.parts.push_back(VolPart(VolPart::Full,IntVector(0,0,0)));
  drawer.draw(puzzles[0]);
// 	for (int i = 0; i < puzzles.size(); i++)
// 	{
// 		PuzzlePart p = puzzles[i];
// 		p.shift(IntVector(i*3));
// 		drawer.draw(p);
// 	}
	//glutSolidTeapot(2.0);
  //glutSolidCube(2.);
  //glTranslatef(2.,0.,0.);
  //glutSolidCube(2.);

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

