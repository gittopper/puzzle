#include "solver.h"
#include "utils.h"
#include "print.h"
#include "pieceshower.h"

namespace Geometry
{
  Solver::Solver(VolumePuzzle& puzzleInstance) :
   box(0,0,0),
   numPlaced(0),
   maxSol(0),
   progress(0),
   seekedPuzzle(9),
   puzzle(puzzleInstance)
  {
    box = puzzle.getEmptyBox();
    pieces = puzzle.getPieces();
    dimX = puzzle.getXDim();
    dimY = puzzle.getYDim();
    dimZ = puzzle.getZDim();

    seekedPuzzle.parts.push_back(VolPart(VolPart::Full,Vector(0,0,0)));
    seekedPuzzle.parts.push_back(VolPart(VolPart::Full,Vector(0,0,1)));
    seekedPuzzle.parts.push_back(VolPart(VolPart::Angle,Vector(0,1,0),Vector(0,1,1)));
    seekedPuzzle.parts.push_back(VolPart(VolPart::Angle,Vector(0,1,1),Vector(1,1,0)));
  }
  void Solver::remove(const Piece& part)
  {
    box.remove(part.parts);
    numPlaced--;
  }
  void Solver::place(const Piece& part, Box& b)
  {
    box.add(part.parts);
    numPlaced++;
    return;
  }
  bool Solver::couldPlace(const Piece& part, bool& matched) const
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
  bool Solver::hasSqueezed(const Piece& part) const
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
  bool Solver::tryToPlace(const Piece& part)
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

  bool Solver::verifyAlgorithm()
  {
    Box tt = puzzle.getEmptyBox();

    for(unsigned i =0; i < solution.size(); i++)
    {
      tt.add(solution[i].parts);
    }
    return tt == box;
  }

  bool Solver::foundNewSolution()
  {
    if (puzzle.addSolution(solution))
    {
      printLastSolution(puzzle);
      maxSol = numPlaced;
      return true;
    }
    return false;
  }

  bool Solver::puzzleCouldBePlacedSomewhere(const Piece& partToCheck)
  {
    Piece part = partToCheck;
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
      Piece part2 = part;
      for (int j = 0; j < 4; j++)
      {
        part2.rotate(RotateZ).centralize();
        BBox boundaries;
        part2.getBBox(boundaries);
        int xmax = dimX - boundaries.maxV[0];
        int ymax = dimY - boundaries.maxV[1];
        int zmax = dimZ - boundaries.maxV[2];

        if (xmax < 1 || ymax < 1 || zmax < 1 ) continue;

        for(int x = 1; x <= xmax;x++)
        {
          for(int y = 1; y <= ymax;y++)
          {
            for(int z = 1; z <= zmax;z++)
            {
              Piece part3 = part2;
              part3.shift(Vector(x,y,z));
              if (tryToPlace(part3))
              {
                remove(part3);
                return true;
              }
            }
          }
        }
      }
    }
    return false;
  }

  void Solver::solve()
  {
    BREAK_ON_LINE(verifyAlgorithm());
    if (maxSol<numPlaced && (numPlaced < pieces.size() - 1))
    {
      foundNewSolution();
    }
    if(numPlaced == pieces.size() - 1 && hasTwoEmpty())
    {
      if (foundNewSolution())
      {
        if(puzzleCouldBePlacedSomewhere(seekedPuzzle))
        {
          cout<<"Found potential solution!"<<endl;
        }
      }
    }
    if (numPlaced == pieces.size())
    {
      foundNewSolution();
      return;
    }
    for(unsigned iPuzzle = 0; iPuzzle <pieces.size(); iPuzzle ++)
    {
      if (pieces[iPuzzle].busy) continue;

    pieces[iPuzzle].busy = true;

      Piece part = pieces[iPuzzle];
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
        Piece part2 = part;
        for (int j = 0; j < 4; j++)
        {
          part2.rotate(RotateZ).centralize();
          BBox boundaries;
          part2.getBBox(boundaries);
          int xmax = dimX - boundaries.maxV[0];
          int ymax = dimY - boundaries.maxV[1];
          int zmax = dimZ - boundaries.maxV[2];

          if (xmax < 1 || ymax < 1 || zmax < 1 ) continue;

//           if (numPlaced == 0)
//           {
//             xmax = xmax / 2 + 1;
//             ymax = ymax / 2 + 1;
//             zmax = zmax / 2 + 1;
//           }


          for(int x = 1; x <= xmax;x++)
          {
            for(int y = 1; y <= ymax;y++)
            {
              for(int z = 1; z <= zmax;z++)
              {
                Piece part3 = part2;
                part3.shift(Vector(x,y,z));
                if (tryToPlace(part3))
                {
                  solution.pieces.push_back(part3);

          //Mat t = part3.getRotationMatrix(pieces[iPuzzle]);

                  solve();
                  remove(part3);
                  solution.pieces.pop_back();
                }
              }
            }
          }
        }
      }
      pieces[iPuzzle].busy = false;
      if (numPlaced == 0) return; //we should find all solutions only for one first figure
      if (numPlaced == 1) 
      {
        cout <<++progress<<endl;
      }
    }
  }
}
