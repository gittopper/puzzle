#pragma once
#include "threads.h"
#include "puzzlepart.h"

class Gfx: public Runnable {
public:
	Gfx(): myID(0){}
	void init(int argc, char ** argv);
	virtual void* run();
private:
	int _argc;
	char ** _argv;
	int myID;
};

void Display();

extern Geometry::PuzzlesSet puzzlesSetToShow;
