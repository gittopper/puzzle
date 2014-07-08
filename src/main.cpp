#include "puzzle55.h"

#include "geometry.h"
#include "print.h"
#include "solver.h"
#include "utils.h"

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

void rotatePuzzles(vector<PuzzlePart>& puzzles, Mat rot)
{
  for(vector<PuzzlePart>::iterator it = puzzles.begin(); it != puzzles.end(); it++)
  {
    (*it).rotate(rot);
  }
}

bool makeGeneralTests()
{
  BREAK_ON_LINE(IntVector(0,0,1).rotate(RotateX) == IntVector(0,1,0));
  BREAK_ON_LINE(IntVector(0,0,1).rotate(RotateX).rotate(RotateX) == IntVector(0,0,-1));

  BREAK_ON_LINE(IntVector(1,0,0).rotate(RotateY) == IntVector(0,0,1));
  BREAK_ON_LINE(IntVector(1,0,0).rotate(RotateY).rotate(RotateY) == IntVector(-1,0,0));

  BREAK_ON_LINE(IntVector(0,1,0).rotate(RotateZ) == IntVector(1,0,0));
  BREAK_ON_LINE(IntVector(0,1,0).rotate(RotateZ).rotate(RotateZ) == IntVector(0,-1,0));


  vector<PuzzlePart> puzzles = generateWoodPuzzles();
  PuzzlePart part = puzzles[0];
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

  Mat rotX(1,0,0, 0,0,-1, 0,1,0);
  Mat rotZ(0,-1,0, 1,0,0, 0,0,1);

  vector<PuzzlePart> rotatedPuzzles = puzzles;
  rotatePuzzles(rotatedPuzzles,rotX);
  BREAK_ON_LINE(puzzlesCouldBeCombined(rotatedPuzzles,puzzles));
  rotatePuzzles(rotatedPuzzles,rotZ);
  BREAK_ON_LINE(puzzlesCouldBeCombined(rotatedPuzzles,puzzles));

  Mat r = m * m.inverse();
  Mat e(IntVector(1,0,0),IntVector(0,1,0),IntVector(0,0,1));
  BREAK_ON_LINE(r == e);
  IntVector v = e * IntVector(-1,1,2);
  BREAK_ON_LINE(v == IntVector(-1,1,2));
  return true;
}

void solvePuzzle()
{
  BREAK_ON_LINE(makeGeneralTests());
//   Solver testSolver(2,2,2,generateTestPuzzles());

  vector<PuzzlePart> puzzles = generateWoodPuzzles();
  Solver solver(3,4,2,puzzles);
  cout << puzzles;
  solver.solve();

//  Solver somaSolver(3,3,3,generateSomaPuzzles());
//  somaSolver.solve();

  cout << "Press any key to exit..."<<flush;
  cin.get();
}
int main()
{
  solvePuzzle();
  //solve55();

  return 0;
}