#include "puzzle55.h"

#include "geometry.h"
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

int main(int argc, char ** argv)
{
  return realMain(argc, argv);
  //solve55();

  return 0;
}