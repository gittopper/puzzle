#include "solver.h"
#include "utils.h"
#include "print.h"
#include "puzzlepartshower.h"
#include "visualization.h"
#include "glut.h"

namespace Geometry
{
  Solver::Solver(int xDim,int yDim,int zDim, const PuzzlesSet availablePuzzles):
    puzzles(availablePuzzles),dimX(xDim),dimY(yDim),dimZ(zDim),box(0,0,0),numPlaced(0),maxSol(0),progress(0),seekedPuzzle(9)
  {
    box = generateEmptyBox_(dimX,dimY,dimZ);

    seekedPuzzle.parts.push_back(VolPart(VolPart::Full,FloatVector(0,0,0)));
    seekedPuzzle.parts.push_back(VolPart(VolPart::Full,FloatVector(0,0,1)));
    seekedPuzzle.parts.push_back(VolPart(VolPart::Angle,FloatVector(0,1,0),FloatVector(0,1,1)));
    seekedPuzzle.parts.push_back(VolPart(VolPart::Angle,FloatVector(0,1,1),FloatVector(1,1,0)));
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

  PuzzlesSet Solver::getNormalized(const PuzzlesSet& sol,Mat&rotation)
  {
    PuzzlesSet ordered;
    for(unsigned i = 1; i<=puzzles.size();i++)
    {
      for(unsigned j = 0; j<sol.size();j++)
      {
        if (sol[j].number == i) ordered.puzzles.push_back(sol[j]);
      }
    }
    const PuzzlePart& part = ordered[0];
    rotation = part.getRotationMatrix(puzzles[part.number-1]);
    BREAK_ON_LINE(rotation.det()==1);
    ordered.rotate(rotation);

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

  Box Solver::generateEmptyBox_(int dimX,int dimY,int dimZ) const
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
            cleanBox.el(x,y,z) = VolPart(isWall ? VolPart::Full : VolPart::Empty,FloatVector(x,y,z),FloatVector(0,0,0),isWall);
          }
        }
      }
    }
    return cleanBox;
  }

  bool Solver::newSolution()
  {
    Mat rot;
    PuzzlesSet sol = getNormalized(solution,rot);

    for(unsigned iSol = 0; iSol < solutions.size(); iSol ++)
    {

      if (solutions[iSol] == sol) return false;

    }
    solutions.push_back(sol);
    transforms.push_back(rot);
    return true;
  }
  void Solver::drawSolution(const PuzzlesSet& s, Mat rot) const
  {
    for (unsigned i = 0; i < s.size(); i++)
    {
      cout << ( i > 0 ? "," : "") << s[i].number;
    }
    Box tt = box;
    tt.rotate(rot);
    cout << endl << tt <<endl;

    Box emptyBox(generateEmptyBox_(tt.getDimX()-2,tt.getDimY()-2,tt.getDimZ()-2));
    for (unsigned i = 0; i < s.size(); i++)
    {
      emptyBox.add(s[i].parts);
      cout << emptyBox<<endl;
      emptyBox.remove(s[i].parts);
    }
	PuzzlesSet visSol;
	for (int i=0;i<s.size();i++)
	{
		visSol.puzzles.push_back(s[i]);
		lockPuzzlesToShow.acquire();
		puzzlesSetToShow = visSol;
		lockPuzzlesToShow.release();
		Sleep(1000);
	}
  }
  bool Solver::tryToShow()
  {
    maxSol = numPlaced;
    if (newSolution())
    {
      cout << "Solution number " << solutions.size() << ":"<< endl;
      cout << "Number of figures is " << numPlaced << ":"<< endl;
      cout << solutions[solutions.size()-1] << endl;
      drawSolution(solutions[solutions.size()-1],transforms[transforms.size()-1]);
      return true;
    }
    return false;
  }

  bool Solver::puzzleCouldBePlacedSomewhere(const PuzzlePart& partToCheck)
  {
    PuzzlePart part = partToCheck;
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

        for(int x = 1; x <= xmax;x++)
        {
          for(int y = 1; y <= ymax;y++)
          {
            for(int z = 1; z <= zmax;z++)
            {
              PuzzlePart part3 = part2;
              part3.shift(FloatVector(x,y,z));
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
    if (maxSol<numPlaced && (numPlaced < puzzles.size() - 1))
    {
      tryToShow();
    }
    if(numPlaced == puzzles.size() - 1 && hasTwoEmpty())
    {
      if (tryToShow())
      {
        if(puzzleCouldBePlacedSomewhere(seekedPuzzle))
        {
          cout<<"Found potential solution!"<<endl;
        }
      }
    }
    if (numPlaced == puzzles.size())
    {
      tryToShow();
      return;
    }
    for(unsigned iPuzzle = 0; iPuzzle <puzzles.size(); iPuzzle ++)
    {
      if (puzzles[iPuzzle].busy) continue;

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
                PuzzlePart part3 = part2;
                part3.shift(FloatVector(x,y,z));
                if (tryToPlace(part3))
                {
                  solution.puzzles.push_back(part3);

				  //Mat t = part3.getRotationMatrix(puzzles[iPuzzle]);

                  solve();
                  remove(part3);
                  solution.puzzles.pop_back();
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