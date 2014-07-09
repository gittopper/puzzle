#pragma once

#include "geometry.h"

namespace Geometry
{


  class Solver
  {
  public:
    Solver(int xDim,int yDim,int zDim, const PuzzlesSet availablePuzzles);
    virtual ~Solver(){}
    void remove(const PuzzlePart& part);
    void place(const PuzzlePart& part, Box& b);
    bool couldPlace(const PuzzlePart& part, bool& matched) const;
    bool hasSqueezed(const PuzzlePart& part) const;
    bool tryToPlace(const PuzzlePart& part);

    bool hasTwoEmpty() const;

    PuzzlesSet getNormalized(const PuzzlesSet& sol);

    bool verifyAlgorithm();

    bool newSolution();
    void drawSolution(const PuzzlesSet& s) const;
    bool tryToShow();

    void solve();

    bool puzzleCouldBePlacedSomewhere(const PuzzlePart& partToCheck);
    PuzzlesSet& getPuzzles() { return puzzles;}
  protected:
    Box generateEmptyBox_(int dimX,int dimY,int dimZ);

    PuzzlePart seekedPuzzle;

    int dimX, dimY, dimZ;
    Box box;
    PuzzlesSet solution;
    vector<PuzzlesSet> solutions;
    unsigned numPlaced;
    PuzzlesSet puzzles;
    int progress;
    unsigned maxSol;
  };
}