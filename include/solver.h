#pragma once

#include "geometry.h"

namespace Geometry
{


	class Solver
	{
	public:
		Solver(int xDim,int yDim,int zDim, const vector<PuzzlePart> availablePuzzles);
		virtual ~Solver();
		void remove(const PuzzlePart& part);
		void place(const PuzzlePart& part, Box& b);
		bool couldPlace(const PuzzlePart& part, bool& matched) const;
		bool hasSqueezed(const PuzzlePart& part) const;
		bool tryToPlace(const PuzzlePart& part);

		bool hasTwoEmpty() const;

		vector<PuzzlePart> getOrdered(const vector<PuzzlePart >& sol);

		bool verifyAlgorithm();

		bool newSolution();
		void drawSolution(const vector<PuzzlePart>& s) const;
		bool tryToShow();

		void solve();

		vector<PuzzlePart>& getPuzzles() { return puzzles;}
	protected:
		Box generateEmptyBox_(int dimX,int dimY,int dimZ);

		int dimX, dimY, dimZ;
		Box box;
		vector<PuzzlePart> solution;
		vector<vector<PuzzlePart>> solutions;
		int numPlaced;
		vector<PuzzlePart> puzzles;
		int progress;
		int maxSol;
	};
}