#include "utils.h"
#include "puzzle55.h"
#include "solver.h"
#include "print.h"

using namespace Geometry;

PiecesSet  generateWoodPuzzles()
{
  PiecesSet pieces;

  Piece p1(1);
  p1.parts.push_back(VolPart(VolPart::Full,Vector(0,0,0)));
  p1.parts.push_back(VolPart(VolPart::Full,Vector(0,1,1)));
  p1.parts.push_back(VolPart(VolPart::Angle,Vector(0,1,0),Vector(1,1,0)));
  p1.parts.push_back(VolPart(VolPart::Angle,Vector(0,0,1),Vector(0,-1,1)));
  pieces.pieces.push_back(p1);

  Piece p2(2);
  p2.parts.push_back(VolPart(VolPart::Full,Vector(0,0,0)));
  p2.parts.push_back(VolPart(VolPart::Full,Vector(1,0,0)));
  p2.parts.push_back(VolPart(VolPart::Angle,Vector(0,0,1),Vector(1,0,1)));
  p2.parts.push_back(VolPart(VolPart::Angle,Vector(1,1,0),Vector(0,1,1)));
  pieces.pieces.push_back(p2);


  Piece p3(3);
  p3.parts.push_back(VolPart(VolPart::Full,Vector(0,0,0)));
  p3.parts.push_back(VolPart(VolPart::Full,Vector(0,1,1)));
  p3.parts.push_back(VolPart(VolPart::Angle,Vector(0,0,1),Vector(1,0,1)));
  p3.parts.push_back(VolPart(VolPart::Angle,Vector(0,1,0),Vector(-1,0,-1)));
  pieces.pieces.push_back(p3);


  Piece p4(4);
  p4.parts.push_back(VolPart(VolPart::Full,Vector(0,1,0)));
  p4.parts.push_back(VolPart(VolPart::Full,Vector(0,1,1)));
  p4.parts.push_back(VolPart(VolPart::Angle,Vector(0,0,1),Vector(0,-1,-1)));
  p4.parts.push_back(VolPart(VolPart::Angle,Vector(0,2,0),Vector(-1,1,0)));
  pieces.pieces.push_back(p4);


  Piece p5(5);
  p5.parts.push_back(VolPart(VolPart::Full,Vector(0,0,0)));
  p5.parts.push_back(VolPart(VolPart::Full,Vector(0,1,0)));
  p5.parts.push_back(VolPart(VolPart::Angle,Vector(0,0,1),Vector(0,1,1)));
  p5.parts.push_back(VolPart(VolPart::Angle,Vector(0,2,0),Vector(-1,1,0)));
  pieces.pieces.push_back(p5);


  Piece p6(6);
  p6.parts.push_back(VolPart(VolPart::Full,Vector(0,0,0)));
  p6.parts.push_back(VolPart(VolPart::Full,Vector(0,1,0)));
  p6.parts.push_back(VolPart(VolPart::Angle,Vector(0,0,1),Vector(1,0,1)));
  p6.parts.push_back(VolPart(VolPart::Angle,Vector(0,2,0),Vector(0,1,1)));
  pieces.pieces.push_back(p6);


  Piece p7(7);
  p7.parts.push_back(VolPart(VolPart::Full,Vector(1,0,0)));
  p7.parts.push_back(VolPart(VolPart::Full,Vector(1,0,1)));
  p7.parts.push_back(VolPart(VolPart::Angle,Vector(0,0,1),Vector(-1,0,-1)));
  p7.parts.push_back(VolPart(VolPart::Angle,Vector(1,1,0),Vector(0,1,1)));
  pieces.pieces.push_back(p7);


  Piece p8(8);
  p8.parts.push_back(VolPart(VolPart::Full,Vector(0,0,0)));
  p8.parts.push_back(VolPart(VolPart::Full,Vector(0,1,0)));
  p8.parts.push_back(VolPart(VolPart::Angle,Vector(0,0,1),Vector(1,0,1)));
  p8.parts.push_back(VolPart(VolPart::Angle,Vector(0,1,1),Vector(0,1,1)));
  pieces.pieces.push_back(p8);

  return pieces;
}
PiecesSet generateSomaPuzzles()
{
  PiecesSet pieces;

  Piece p1(1);
  p1.parts.push_back(VolPart(VolPart::Full,Vector(0,0,0)));
  p1.parts.push_back(VolPart(VolPart::Full,Vector(0,1,0)));
  p1.parts.push_back(VolPart(VolPart::Full,Vector(1,0,0)));
  p1.parts.push_back(VolPart(VolPart::Full,Vector(1,0,1)));
  pieces.pieces.push_back(p1);

  Piece p2(2);
  p2.parts.push_back(VolPart(VolPart::Full,Vector(1,0,0)));
  p2.parts.push_back(VolPart(VolPart::Full,Vector(1,0,1)));
  p2.parts.push_back(VolPart(VolPart::Full,Vector(1,1,0)));
  p2.parts.push_back(VolPart(VolPart::Full,Vector(0,1,0)));
  pieces.pieces.push_back(p2);


  Piece p3(3);
  p3.parts.push_back(VolPart(VolPart::Full,Vector(0,0,0)));
  p3.parts.push_back(VolPart(VolPart::Full,Vector(1,0,0)));
  p3.parts.push_back(VolPart(VolPart::Full,Vector(1,0,1)));
  p3.parts.push_back(VolPart(VolPart::Full,Vector(1,1,0)));
  pieces.pieces.push_back(p3);


  Piece p4(4);
  p4.parts.push_back(VolPart(VolPart::Full,Vector(1,0,0)));
  p4.parts.push_back(VolPart(VolPart::Full,Vector(1,1,0)));
  p4.parts.push_back(VolPart(VolPart::Full,Vector(2,1,0)));
  p4.parts.push_back(VolPart(VolPart::Full,Vector(0,1,0)));
  pieces.pieces.push_back(p4);


  Piece p5(5);
  p5.parts.push_back(VolPart(VolPart::Full,Vector(1,0,0)));
  p5.parts.push_back(VolPart(VolPart::Full,Vector(1,1,0)));
  p5.parts.push_back(VolPart(VolPart::Full,Vector(0,1,0)));
  p5.parts.push_back(VolPart(VolPart::Full,Vector(0,2,0)));
  pieces.pieces.push_back(p5);


  Piece p6(6);
  p6.parts.push_back(VolPart(VolPart::Full,Vector(2,0,0)));
  p6.parts.push_back(VolPart(VolPart::Full,Vector(0,1,0)));
  p6.parts.push_back(VolPart(VolPart::Full,Vector(1,1,0)));
  p6.parts.push_back(VolPart(VolPart::Full,Vector(2,1,0)));
  pieces.pieces.push_back(p6);


  Piece p7(7);
  p7.parts.push_back(VolPart(VolPart::Full,Vector(1,0,0)));
  p7.parts.push_back(VolPart(VolPart::Full,Vector(0,1,0)));
  p7.parts.push_back(VolPart(VolPart::Full,Vector(1,1,0)));
  pieces.pieces.push_back(p7);

  return pieces;
}

void solve55()
{
  vector<vector<int> > pieces;

  vector<int> puzzle1;
  puzzle1.push_back(3);
  puzzle1.push_back(6);
  puzzle1.push_back(8);
  pieces.push_back(puzzle1);

  vector<int> puzzle2;
  puzzle2.push_back(0);
  puzzle2.push_back(2);
  puzzle2.push_back(6);
  pieces.push_back(puzzle2);

  vector<int> puzzle3;
  puzzle3.push_back(1);
  puzzle3.push_back(3);
  puzzle3.push_back(5);
  pieces.push_back(puzzle3);

  vector<int> puzzle4;
  puzzle4.push_back(4);
  puzzle4.push_back(5);
  puzzle4.push_back(6);
  pieces.push_back(puzzle4);

  vector<int> puzzle5;
  puzzle5.push_back(2);
  puzzle5.push_back(5);
  puzzle5.push_back(9);
  pieces.push_back(puzzle5);

  vector<int> puzzle6;
  puzzle6.push_back(0);
  puzzle6.push_back(6);
  puzzle6.push_back(9);
  pieces.push_back(puzzle6);

  vector<int> puzzle7;
  puzzle7.push_back(0);
  puzzle7.push_back(2);
  puzzle7.push_back(9);
  pieces.push_back(puzzle7);

  vector<int> puzzle8;
  puzzle8.push_back(0);
  puzzle8.push_back(4);
  puzzle8.push_back(9);
  pieces.push_back(puzzle8);

  Puzzle55 puzzle55(pieces);
  puzzle55.printFigures();
  puzzle55.solve();
}

SolvingTask::SolvingTask(VolumePuzzle& puzzleToSolve) :
solver(puzzleToSolve)
{
}

void* SolvingTask::run()
{
  solver.solve();
  return reinterpret_cast<void*>(0);
}


void printLastSolution(const VolumePuzzle& puzzle)
{
  int iSol = puzzle.numFoundSolutions();

  PiecesSet sol;
  puzzle.getSolution(sol, iSol);

  cout << "Solution number " << iSol << ":" << endl;
  cout << "Number of figures is " << sol.size() << ":" << endl;
  cout << sol << endl;

  for (unsigned i = 0; i < sol.size(); i++)
  {
    cout << (i > 0 ? "," : "") << sol[i].number;
  }
  Box box(puzzle.getEmptyBox());
  Box filledBox = box;

  for (unsigned i = 0; i < sol.size(); i++)
  {
    filledBox.add(sol[i].parts);
  }

  cout << endl << filledBox << endl;

  for (unsigned i = 0; i < sol.size(); i++)
  {
    box.add(sol[i].parts);
    cout << box << endl;
    box.remove(sol[i].parts);
  }
}