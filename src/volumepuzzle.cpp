#include "volumepuzzle.h"

using namespace Geometry;

bool VolumePuzzle::addSolution(const PiecesSet& sol)
{
  std::lock_guard<std::mutex> block(lock);
  Mat rot;
  PiecesSet orderedSolution = sol;
  orderedSolution.order();

  PiecesSet normalizedSolution = orderedSolution;

  const Piece& part = orderedSolution[0];
  Piece p = pieces[part.number - 1];
  Mat rotation = part.getRotationMatrix(p);

  BREAK_ON_LINE(rotation.det() == 1);
  p.rotate(rotation.inverse());
  BREAK_ON_LINE(part == p);

  normalizedSolution.rotate(rotation);

  for (unsigned iSol = 0; iSol < normalizedSolutions.size(); iSol++)
  {
    if (normalizedSolutions[iSol] == normalizedSolution) return false;
  }

  solutions.push_back(orderedSolution);
  normalizedSolutions.push_back(normalizedSolution);
  addedSolution();
  return true;
}

//std::mutex VolumePuzzle::lock;

int VolumePuzzle::numFoundSolutions() const
{
  std::lock_guard<std::mutex> block(lock);
  int l = solutions.size();
  return l;
}

void VolumePuzzle::getSolution(PiecesSet& sol, int i) const
{
  std::lock_guard<std::mutex> block(lock);
  sol = solutions[i - 1];
}

VolumePuzzle::VolumePuzzle(int xDim, int yDim, int zDim, const PiecesSet puzzlePieces) :
dimX(xDim),
dimY(yDim),
dimZ(zDim),
pieces(puzzlePieces)
{
  PiecesSet c = puzzlePieces;
  for (int i = 0; i < c.size(); i++)
  {
    c[i].shift(Vector(2 * i, 0, 0));
  }
  addSolution(c);//for debug
}

int VolumePuzzle::getXDim() const
{
  return dimX;
}

int VolumePuzzle::getYDim() const
{
  return dimY;
}

int VolumePuzzle::getZDim() const
{
  return dimZ;
}

Geometry::PiecesSet VolumePuzzle::getPieces() const
{
  return pieces;
}

Geometry::Box VolumePuzzle::getEmptyBox() const
{
  Box cleanBox(dimX + 2, dimY + 2, dimZ + 2);

  for (int x = 0; x < dimX + 2; x++)
  {
    for (int y = 0; y < dimY + 2; y++)
    {
      for (int z = 0; z < dimZ + 2; z++)
      {
        bool isWall = !(x % (dimX + 1)) || !(y % (dimY + 1)) || !(z % (dimZ + 1));
        if (isWall)
        {
          cleanBox.el(x, y, z) = VolPart(isWall ? VolPart::Full : VolPart::Empty, Vector(x, y, z), Vector(0, 0, 0), isWall);
        }
      }
    }
  }
  return cleanBox;
}
