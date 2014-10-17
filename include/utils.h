#pragma once
#include "geometry.h"
#include "solver.h"
#include "threads.h"

Geometry::PiecesSet generateWoodPuzzles();

Geometry::PiecesSet generateSomaPuzzles();

void printLastSolution(const VolumePuzzle& puzzle);

class SolvingTask : public Task
{
public:
  SolvingTask(VolumePuzzle& puzzleToSolve);
  virtual void* run();
private:
  Solver solver;
};

void solve55();