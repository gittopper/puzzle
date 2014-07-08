#include "solver.h"
#include "utils.h"
#include "print.h"

namespace Geometry
{
  Solver::Solver(int xDim,int yDim,int zDim, const vector<PuzzlePart> availablePuzzles):
    puzzles(availablePuzzles),dimX(xDim),dimY(yDim),dimZ(zDim),box(0,0,0),numPlaced(0),maxSol(0),progress(0)
  {
    box = generateEmptyBox_(dimX,dimY,dimZ);
    cout << puzzles;
  }
  void Solver::remove(const PuzzlePart& part)
  {
    box.remove(part.parts);
    numPlaced--;
  }
  void Solver::place(const PuzzlePart& part, Box& b)
  {
    box.add(part.parts);
    numPlaced++;
    return;
  }
  bool Solver::couldPlace(const PuzzlePart& part, bool& matched) const
  {
    matched = false;
    for(unsigned i = 0; i < part.parts.size(); i++)
    {
      const VolPart& vol = part.parts[i];
      if (!box.el(vol.getCoords()).couldPlace(vol)) return false;

      if (matched) continue;
      matched = matched || box.el(vol.getCoords()).shareOneOfSides(vol);

      matched = matched || box.el(vol.getCoords()[0]-1, vol.getCoords()[1], vol.getCoords()[2]).shareOneOfSides(vol);
      matched = matched || box.el(vol.getCoords()[0]+1, vol.getCoords()[1], vol.getCoords()[2]).shareOneOfSides(vol);
      if (matched) continue;

      matched = matched || box.el(vol.getCoords()[0], vol.getCoords()[1]-1, vol.getCoords()[2]).shareOneOfSides(vol);
      matched = matched || box.el(vol.getCoords()[0], vol.getCoords()[1]+1, vol.getCoords()[2]).shareOneOfSides(vol);
      if (matched) continue;

      matched = matched || box.el(vol.getCoords()[0], vol.getCoords()[1], vol.getCoords()[2]-1).shareOneOfSides(vol);
      matched = matched || box.el(vol.getCoords()[0], vol.getCoords()[1], vol.getCoords()[2]+1).shareOneOfSides(vol);
    }
    return true;
  }
  bool Solver::hasSqueezed(const PuzzlePart& part) const
  {
    BBox bbox;
    part.getBBox(bbox);
    bbox.grow();

    for(int x = bbox.minV[0]; x <= bbox.maxV[0];x++)
    {
      for(int y = bbox.minV[1]; y <= bbox.maxV[1];y++)
      {
        for(int z = bbox.minV[2]; z <= bbox.maxV[2];z++)
        {

          //          if (isSqueezed(box.el(x, y, z])) return true;
          BREAK_ON_LINE(box.isSqueezed(box.el(x, y, z)) == box.isSqueezedV2(box.el(x, y, z)));
          if (box.isSqueezedV2(box.el(x, y, z))) return true;
        }
      }
    }
    return false;
  }
  bool Solver::tryToPlace(const PuzzlePart& part)
  {
    bool matched;
    if (!couldPlace(part,matched))
    {
      return false;
    }
    if (numPlaced && !matched)
    {
      return false;
    }
    place(part,box);
    if (hasSqueezed(part))
    {
      remove(part);
      return false;
    }
    return true;
  }
  bool Solver::hasTwoEmpty() const
  {
    for (int x = 1; x <= dimX; x++)
    {
      for (int y = 1; y <= dimY; y++)
      {
        for (int z = 1; z <= dimZ; z++)
        {
          if(box.el(x, y, z).type() == VolPart::Empty && box.checkHalf(box.el(x, y, z)) &&(
            box.el(x+1, y, z).type() == VolPart::Empty && box.checkHalf(box.el(x+1, y, z)) ||
            box.el(x, y+1, z).type() == VolPart::Empty && box.checkHalf(box.el(x, y+1, z)) ||
            box.el(x, y, z+1).type() == VolPart::Empty && box.checkHalf(box.el(x, y, z+1))
            ))
            return true;
        }
      }
    }
    return false;
  }
  vector<vector<PuzzlePart> > solutions;

  vector<PuzzlePart> Solver::getOrdered(const vector<PuzzlePart >& sol)
  {
    vector<PuzzlePart> ordered;
    for(unsigned i = 1; i<=puzzles.size();i++)
    {
      for(unsigned j = 0; j<sol.size();j++)
      {
        if (sol[j].number == i) ordered.push_back(sol[j]);
      }
    }
    return ordered;
  }

  bool Solver::verifyAlgorithm()
  {
    Box tt(generateEmptyBox_(dimX,dimY,dimZ));

    for(unsigned i =0; i < solution.size(); i++)
    {
      tt.add(solution[i].parts);
    }
    return tt == box;
  }

  Box Solver::generateEmptyBox_(int dimX,int dimY,int dimZ)
  {
    Box cleanBox(dimX + 2, dimY + 2, dimZ + 2);

    for (int x = 0; x <= dimX + 1; x++)
    {
      for (int y = 0; y <= dimY + 1; y++)
      {
        for (int z = 0; z <= dimZ + 1; z++)
        {
          bool isWall = !(x % (dimX + 1)) || !(y % (dimY + 1)) || !(z % (dimZ + 1));
          if (isWall)
          {
            cleanBox.el(x,y,z) = VolPart(isWall ? VolPart::Full : VolPart::Empty,IntVector(x,y,z),IntVector(0,0,0),isWall);
          }
        }
      }
    }
    return cleanBox;
  }

  bool Solver::newSolution()
  {
    vector<PuzzlePart> sol = getOrdered(solution);

    for(unsigned iSol = 0; iSol < solutions.size(); iSol ++)
    {

      if (puzzlesCouldBeCombined(solutions[iSol],sol)) return false;

    }
    solutions.push_back(sol);
    return true;
  }
  void Solver::drawSolution(const vector<PuzzlePart>& s) const
  {
    for (unsigned i = 0; i < s.size(); i++)
    {
      cout << ( i > 0 ? "," : "") << s[i].number;
    }
    cout << endl << box;
  }
  bool Solver::tryToShow()
  {
    maxSol = numPlaced;
    if (newSolution())
    {
      cout << "Solution number " << solutions.size() << ":"<< endl;
      cout << "Number of figures is " << numPlaced << ":"<< endl;
      cout << solutions[solutions.size()-1] << endl;
      drawSolution(solutions[solutions.size()-1]);
      return true;
    }
    return false;
  }

  void Solver::solve()
  {
    BREAK_ON_LINE(verifyAlgorithm());
    if (maxSol<numPlaced && (numPlaced < puzzles.size() - 1) || numPlaced == puzzles.size() - 1 && hasTwoEmpty())
    {
      tryToShow();
    }
    if (numPlaced == puzzles.size())
    {
      tryToShow();
      return;
    }
    for(unsigned iPuzzle = 0; iPuzzle <puzzles.size(); iPuzzle ++)
    {
      if (puzzles[iPuzzle].busy) continue;

      if (false && numPlaced == 1 && progress< 1003 ) 
      {
        cout <<++progress<<endl;
        return;
      }
      puzzles[iPuzzle].busy = true;

      PuzzlePart part = puzzles[iPuzzle];
      for (int i = 0; i < 6; i++)
      {
        if (i < 4)
        {
          part.rotate(RotateY);
        }
        else if (i == 4)
        {
          part.rotate(RotateX);
        }else
        {
          part.rotate(RotateX);
          part.rotate(RotateX);
        }
        PuzzlePart part2 = part;
        for (int j = 0; j < 4; j++)
        {
          part2.rotate(RotateZ).centralize();
          BBox boundaries;
          part2.getBBox(boundaries);
          int xmax = dimX - boundaries.maxV[0];
          int ymax = dimY - boundaries.maxV[1];
          int zmax = dimZ - boundaries.maxV[2];

          if (xmax < 1 || ymax < 1 || zmax < 1 ) continue;

          if (numPlaced == 0)
          {
            xmax = xmax / 2 + 1;
            ymax = ymax / 2 + 1;
            zmax = zmax / 2 + 1;
          }


          for(int x = 1; x <= xmax;x++)
          {
            for(int y = 1; y <= ymax;y++)
            {
              for(int z = 1; z <= zmax;z++)
              {
                PuzzlePart part3 = part2;
                part3.shift(IntVector(x,y,z));
                if (tryToPlace(part3))
                {
                  solution.push_back(part3);
                  solve();
                  remove(part3);
                  solution.pop_back();
                }
              }
            }
          }
        }
      }
      puzzles[iPuzzle].busy = false;
      if (numPlaced == 0) return; //we should find all solutions only for one first figure
      if (numPlaced == 1) 
      {
        cout <<++progress<<endl;
      }
    }
  }
}