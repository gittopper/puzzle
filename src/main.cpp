#include "puzzle55.h"

#include "geometry.h"
#include "print.h"
#include "solver.h"
#include "utils.h"
#include "visualization.h"

using namespace Geometry;

void solve55()
{
  vector<vector<int> > puzzles;
  
  vector<int> puzzle1;
  puzzle1.push_back(3);
  puzzle1.push_back(6);
  puzzle1.push_back(8);
  puzzles.push_back(puzzle1);

  vector<int> puzzle2;
  puzzle2.push_back(0);
  puzzle2.push_back(2);
  puzzle2.push_back(6);
  puzzles.push_back(puzzle2);

  vector<int> puzzle3;
  puzzle3.push_back(1);
  puzzle3.push_back(3);
  puzzle3.push_back(5);
  puzzles.push_back(puzzle3);

  vector<int> puzzle4;
  puzzle4.push_back(4);
  puzzle4.push_back(5);
  puzzle4.push_back(6);
  puzzles.push_back(puzzle4);

  vector<int> puzzle5;
  puzzle5.push_back(2);
  puzzle5.push_back(5);
  puzzle5.push_back(9);
  puzzles.push_back(puzzle5);

  vector<int> puzzle6;
  puzzle6.push_back(0);
  puzzle6.push_back(6);
  puzzle6.push_back(9);
  puzzles.push_back(puzzle6);

  vector<int> puzzle7;
  puzzle7.push_back(0);
  puzzle7.push_back(2);
  puzzle7.push_back(9);
  puzzles.push_back(puzzle7);

  vector<int> puzzle8;
  puzzle8.push_back(0);
  puzzle8.push_back(4);
  puzzle8.push_back(9);
  puzzles.push_back(puzzle8);

  Puzzle55 puzzle55(puzzles);
  puzzle55.printFigures();
  puzzle55.solve();

  cout << "Press any key to exit...";
  cin.get();
}

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
int main(int argc, char ** argv)
{
  return realMain(argc, argv);
  solvePuzzle();
  //solve55();

  return 0;
}