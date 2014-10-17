#pragma once
#include "base.h"
#include "threads.h"
#include "piece.h"
#include "mutex.h"
#include "utils.h"
#include "volumepuzzle.h"

class GLRenderer 
{
public:
  void setPuzzleToRender(VolumePuzzle& puzzleToRender);
  virtual ~GLRenderer(){}
protected:
  void initOpenGL();
  void display();
  void drawLCS();
  void resize(int w, int h);

  void rotateX(float x);
  void rotateY(float y);

  void mouseMove(int x, int y);

  void mouseLButtonDown(int x, int y);
  void mouseLButtonUp(int x, int y);

  void mouseRButtonDown(int x, int y);
  void mouseRButtonUp(int x, int y);

  void wheelUp(int x, int y);
  void wheelDown(int x, int y);

  void showSolution(int sol);
  int curSol, maxSol;
  virtual void addMenuEntry(int i){}

  const VolumePuzzle* puzzle;
  int w, h;
  float zoom;

  float rotate_y;
  float rotate_x;

  float rx0, ry0, xm, ym;
  vector<Vector> colors;
};

