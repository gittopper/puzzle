#include "solver.h"

namespace Geometry
{
	Solver::Solver(const Box initialBox, const vector<PuzzlePart> availablePuzzles):
		box(initialBox),puzzles(availablePuzzles)
	{
	}
	void Solver::remove(const PuzzlePart& part)
	{
		for(unsigned i = 0; i < part.parts.size(); i++)
		{
			const VolPart& vol = part.parts[i];
			box.el(vol.getCoords()) -= vol;
		}
		numPlaced--;
	}
	void Solver::place(const PuzzlePart& part, Box& b)
	{
		for(unsigned i = 0; i < part.parts.size(); i++)
		{
			const VolPart& vol = part.parts[i];
			b.el(vol.getCoords()) += vol;
		}
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
	bool Solver::isSqueezed(const VolPart& vol) const
	{
		if (vol.type() != VolPart::Angle) return false;
		BREAK_ON_LINE(!vol.getDir()[0] || !vol.getDir()[1] || !vol.getDir()[2]);
		int n = 0;
		if (vol.getDir()[0] != 0)
		{
			const VolPart& nVol = box.el(vol.getCoords()[0]+vol.getDir()[0], vol.getCoords()[1], vol.getCoords()[2]);
			if (nVol.type() == VolPart::Full)
			{
				n++;
			}
			else if (nVol.type() == VolPart::Angle)
			{
				if (vol.getDir()[0] * nVol.getDir()[0] >= 0)
				{
					n++;
				}
			}
		}
		if (vol.getDir()[1] != 0)
		{
			const VolPart& nVol = box.el(vol.getCoords()[0], vol.getCoords()[1]+vol.getDir()[1], vol.getCoords()[2]);
			if (nVol.type() == VolPart::Full)
			{
				n++;
			}
			else if (nVol.type() == VolPart::Angle)
			{
				if (vol.getDir()[1] * nVol.getDir()[1] >= 0)
				{
					n++;
				}
			}
		}
		if (vol.getDir()[2] != 0)
		{
			const VolPart& nVol = box.el(vol.getCoords()[0], vol.getCoords()[1], vol.getCoords()[2]+vol.getDir()[2]);
			if (nVol.type() == VolPart::Full)
			{
				n++;
			}
			else if (nVol.type() == VolPart::Angle)
			{
				if (vol.getDir()[2] * nVol.getDir()[2] >= 0)
				{
					n++;
				}
			}
		}
		return n>1;
	}
	bool Solver::isSqueezedV2(const VolPart& vol) const
	{
		if (vol.type() != VolPart::Angle) return false;

		BREAK_ON_LINE(dot(vol.getDir(),vol.getDir()) == 2);
		int n = 0;
		if (vol.getDir()[0] > 0)
		{
			const VolPart& nVol = box.el(vol.getCoords()[0]+1, vol.getCoords()[1], vol.getCoords()[2]);
			if (nVol.type() == VolPart::Full)
			{
				n++;
			}
			else if (nVol.hasSide(0,0)) n++;
		}
		if (vol.getDir()[0] < 0)
		{
			const VolPart& nVol = box.el(vol.getCoords()[0]-1, vol.getCoords()[1], vol.getCoords()[2]);
			if (nVol.type() == VolPart::Full || nVol.hasSide(0,1))
			{
				n++;
			}
		}

		if (vol.getDir()[1] > 0)
		{
			const VolPart& nVol = box.el(vol.getCoords()[0], vol.getCoords()[1]+1, vol.getCoords()[2]);
			if (nVol.type() == VolPart::Full || nVol.hasSide(1,0))
			{
				n++;
			}
		}
		if (vol.getDir()[1] < 0)
		{
			const VolPart& nVol = box.el(vol.getCoords()[0], vol.getCoords()[1]-1, vol.getCoords()[2]);
			if (nVol.type() == VolPart::Full || nVol.hasSide(1,1))
			{
				n++;
			}
		}

		if (vol.getDir()[2] > 0)
		{
			const VolPart& nVol = box.el(vol.getCoords()[0], vol.getCoords()[1], vol.getCoords()[2]+1);
			if (nVol.type() == VolPart::Full || nVol.hasSide(2,0))
			{
				n++;
			}
		}
		if (vol.getDir()[2] < 0)
		{
			const VolPart& nVol = box.el(vol.getCoords()[0], vol.getCoords()[1], vol.getCoords()[2]-1);
			if (nVol.type() == VolPart::Full || nVol.hasSide(2,1))
			{
				n++;
			}
		}

		return n > 1;
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
					BREAK_ON_LINE(isSqueezed(box.el(x, y, z]) == isSqueezedV2(box.el(x, y, z]));
					if (isSqueezedV2(box.el(x, y, z])) return true;
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
	bool Solver::checkHalf(const VolPart& vol) const
	{
		int x = vol.getCoords()[0];
		int y = vol.getCoords()[1];
		int z = vol.getCoords()[2];
		return 
			box.el(x-1, y, z).type() == VolPart::Angle && box.el(x-1, y, z).getDir()[0]>0 ||
			box.el(x+1, y, z).type() == VolPart::Angle && box.el(x+1, y, z).getDir()[0]<0 ||
			box.el(x, y-1, z).type() == VolPart::Angle && box.el(x, y-1, z).getDir()[1]>0 ||
			box.el(x, y+1, z).type() == VolPart::Angle && box.el(x, y+1, z).getDir()[1]<0 ||
			box.el(x, y, z-1).type() == VolPart::Angle && box.el(x, y, z-1).getDir()[2]>0 ||
			box.el(x, y, z+1).type() == VolPart::Angle && box.el(x, y, z+1).getDir()[2]<0;
	}
	bool Solver::hasTwoEmpty() const
	{
		for (int x = 1; x <= dimX; x++)
		{
			for (int y = 1; y <= dimY; y++)
			{
				for (int z = 1; z <= dimZ; z++)
				{
					if(box.el(x, y, z).type() == VolPart::Empty && checkHalf(box.el(x, y, z) &&(
						box.el(x+1, y, z).type() == VolPart::Empty && checkHalf(box.el(x+1, y, z) ||
						box.el(x, y+1, z).type() == VolPart::Empty && checkHalf(box.el(x, y+1, z) ||
						box.el(x, y, z+1).type() == VolPart::Empty && checkHalf(box.el(x, y, z+1)
						))
						return true;
				}
			}
		}
		return false;
	}
	vector<vector<PuzzlePart> > solutions;

	vector<PuzzlePart> getOrdered(const vector<PuzzlePart >& sol)
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
		Box tt;
		initBox(tt,dimX,dimY,dimZ);
		int n = numPlaced;
		for(unsigned i =0; i < solution.size(); i++)
		{
			place(solution[i],tt);
		}
		numPlaced = n;
		return tt == box;
	}

	bool Solver::newSolution()
	{
		vector<PuzzlePart> sol = getOrdered(solution);

		for(unsigned iSol = 0; iSol < solutions.size(); iSol ++)
		{
			if (solutions[iSol].size() != sol.size() && sol.size()) continue;

			vector<PuzzlePart>& prevSol = solutions[iSol];
			for(unsigned i=0;i<prevSol.size();i++)
			{
				if (prevSol[i].number != sol[i].number) continue;
			}

			Mat rot1 = prevSol[0].getLCS();
			Mat rot2 = sol[0].getLCS();

			Mat res = rot2 * rot1.inverse();
			IntVector prevShift = -prevSol[0].getZero();
			IntVector shift = sol[0].getZero();

			bool theSame = true;

			for(unsigned i=0;i<sol.size();i++)
			{
				PuzzlePart p = prevSol[i];

				p.shift(prevShift).rotate(res).shift(shift);
				theSame = theSame && p == sol[i];
				if (!theSame) break;
			}

			if (theSame)
			{
				return false;
			}
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
		//     if (maxSol<numPlaced && (numPlaced < puzzles.size() - 1) || numPlaced == puzzles.size() - 1 && hasTwoEmpty())
		//     {
		//       tryToShow();
		//     }
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
			if (numPlaced == 0) return; //first figure only once should be checked
			if (numPlaced == 1) 
			{
				cout <<++progress<<endl;
			}
		}
	}
}