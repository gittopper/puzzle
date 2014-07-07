#include "geometry.h"
#include "utils.h"

void makeTests(Solver& solver)
{
  BREAK_ON_LINE(IntVector(0,0,1).rotate(RotateX) == IntVector(0,1,0));
  BREAK_ON_LINE(IntVector(0,0,1).rotate(RotateX).rotate(RotateX) == IntVector(0,0,-1));

  BREAK_ON_LINE(IntVector(1,0,0).rotate(RotateY) == IntVector(0,0,1));
  BREAK_ON_LINE(IntVector(1,0,0).rotate(RotateY).rotate(RotateY) == IntVector(-1,0,0));

  BREAK_ON_LINE(IntVector(0,1,0).rotate(RotateZ) == IntVector(1,0,0));
  BREAK_ON_LINE(IntVector(0,1,0).rotate(RotateZ).rotate(RotateZ) == IntVector(0,-1,0));


  PuzzlePart part = solver.puzzles[0];
  part.rotate(RotateX);
  part.centralize();

  PuzzlePart p1(1);
  p1.parts.push_back(VolPart(VolPart::Full,IntVector(0,0,1)));
  p1.parts.push_back(VolPart(VolPart::Full,IntVector(0,1,0)));
  p1.parts.push_back(VolPart(VolPart::Angle,IntVector(0,0,0),IntVector(1,0,-1)));
  p1.parts.push_back(VolPart(VolPart::Angle,IntVector(0,1,1),IntVector(0,1,1)));

  bool areEqual = part == p1;
  BREAK_ON_LINE(areEqual);

  Mat m(IntVector(0,-1,0),IntVector(0,0,1),IntVector(1,0,0));
  Mat r = m * m.inverse();
  Mat e(IntVector(1,0,0),IntVector(0,1,0),IntVector(0,0,1));
  BREAK_ON_LINE(r == e);
  IntVector v = e * IntVector(-1,1,2);
  BREAK_ON_LINE(v == IntVector(-1,1,2));
}

void solvePuzzle()
{
  Solver solver;

  //makeTests(solver);

  solver.solve();

  cout << "Press any key to exit..."<<flush;
  cin.get();
}