#pragma once

#include "geometry.h"

#include "volumepuzzle.h"

namespace Geometry
{

  class Solver
  {
  public:
    Solver(VolumePuzzle& puzzle);

  void solve();
  protected:
  void remove(const Piece& part);
    void place(const Piece& part, Box& b);
    bool couldPlace(const Piece& part, bool& matched) const;
    bool hasSqueezed(const Piece& part) const;
    bool tryToPlace(const Piece& part);

    bool hasTwoEmpty() const;

    bool verifyAlgorithm();

    bool newSolution();
    bool foundNewSolution();

    bool puzzleCouldBePlacedSomewhere(const Piece& partToCheck);

    Piece seekedPuzzle;
  VolumePuzzle& puzzle;
    int dimX, dimY, dimZ;
    Box box;
    PiecesSet solution;
    unsigned numPlaced;
    PiecesSet pieces;
    int progress;
    unsigned maxSol;
  };
}
