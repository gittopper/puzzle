#include "utils.h"

using namespace Geometry;

vector<PuzzlePart>  generateWoodPuzzles()
{
  vector<PuzzlePart> puzzles;

  PuzzlePart p1(1);
  p1.parts.push_back(VolPart(VolPart::Full,IntVector(0,0,0)));
  p1.parts.push_back(VolPart(VolPart::Full,IntVector(0,1,1)));
  p1.parts.push_back(VolPart(VolPart::Angle,IntVector(0,1,0),IntVector(1,1,0)));
  p1.parts.push_back(VolPart(VolPart::Angle,IntVector(0,0,1),IntVector(0,-1,1)));
  puzzles.push_back(p1);

  PuzzlePart p2(2);
  p2.parts.push_back(VolPart(VolPart::Full,IntVector(0,0,0)));
  p2.parts.push_back(VolPart(VolPart::Full,IntVector(1,0,0)));
  p2.parts.push_back(VolPart(VolPart::Angle,IntVector(0,0,1),IntVector(1,0,1)));
  p2.parts.push_back(VolPart(VolPart::Angle,IntVector(1,1,0),IntVector(0,1,1)));
  puzzles.push_back(p2);


  PuzzlePart p3(3);
  p3.parts.push_back(VolPart(VolPart::Full,IntVector(0,0,0)));
  p3.parts.push_back(VolPart(VolPart::Full,IntVector(0,1,1)));
  p3.parts.push_back(VolPart(VolPart::Angle,IntVector(0,0,1),IntVector(1,0,1)));
  p3.parts.push_back(VolPart(VolPart::Angle,IntVector(0,1,0),IntVector(-1,0,-1)));
  puzzles.push_back(p3);


  PuzzlePart p4(4);
  p4.parts.push_back(VolPart(VolPart::Full,IntVector(0,1,0)));
  p4.parts.push_back(VolPart(VolPart::Full,IntVector(0,1,1)));
  p4.parts.push_back(VolPart(VolPart::Angle,IntVector(0,0,1),IntVector(0,-1,-1)));
  p4.parts.push_back(VolPart(VolPart::Angle,IntVector(0,2,0),IntVector(-1,1,0)));
  puzzles.push_back(p4);


  PuzzlePart p5(5);
  p5.parts.push_back(VolPart(VolPart::Full,IntVector(0,0,0)));
  p5.parts.push_back(VolPart(VolPart::Full,IntVector(0,1,0)));
  p5.parts.push_back(VolPart(VolPart::Angle,IntVector(0,0,1),IntVector(0,1,1)));
  p5.parts.push_back(VolPart(VolPart::Angle,IntVector(0,2,0),IntVector(-1,1,0)));
  puzzles.push_back(p5);


  PuzzlePart p6(6);
  p6.parts.push_back(VolPart(VolPart::Full,IntVector(0,0,0)));
  p6.parts.push_back(VolPart(VolPart::Full,IntVector(0,1,0)));
  p6.parts.push_back(VolPart(VolPart::Angle,IntVector(0,0,1),IntVector(1,0,1)));
  p6.parts.push_back(VolPart(VolPart::Angle,IntVector(0,2,0),IntVector(0,1,1)));
  puzzles.push_back(p6);


  PuzzlePart p7(7);
  p7.parts.push_back(VolPart(VolPart::Full,IntVector(1,0,0)));
  p7.parts.push_back(VolPart(VolPart::Full,IntVector(1,0,1)));
  p7.parts.push_back(VolPart(VolPart::Angle,IntVector(0,0,1),IntVector(0,-1,-1)));
  p7.parts.push_back(VolPart(VolPart::Angle,IntVector(1,1,0),IntVector(0,1,1)));
  puzzles.push_back(p7);


  PuzzlePart p8(8);
  p8.parts.push_back(VolPart(VolPart::Full,IntVector(0,0,0)));
  p8.parts.push_back(VolPart(VolPart::Full,IntVector(0,1,0)));
  p8.parts.push_back(VolPart(VolPart::Angle,IntVector(0,0,1),IntVector(1,0,1)));
  p8.parts.push_back(VolPart(VolPart::Angle,IntVector(0,1,1),IntVector(0,1,1)));
  puzzles.push_back(p8);

  return puzzles;
}
vector<Geometry::PuzzlePart> generateSomaPuzzles()
{
  vector<PuzzlePart> puzzles;

  PuzzlePart p1(1);
  p1.parts.push_back(VolPart(VolPart::Full,IntVector(0,0,0)));
  p1.parts.push_back(VolPart(VolPart::Full,IntVector(0,1,0)));
  p1.parts.push_back(VolPart(VolPart::Full,IntVector(1,0,0)));
  p1.parts.push_back(VolPart(VolPart::Full,IntVector(1,0,1)));
  puzzles.push_back(p1);

  PuzzlePart p2(2);
  p2.parts.push_back(VolPart(VolPart::Full,IntVector(1,0,0)));
  p2.parts.push_back(VolPart(VolPart::Full,IntVector(1,0,1)));
  p2.parts.push_back(VolPart(VolPart::Full,IntVector(1,1,0)));
  p2.parts.push_back(VolPart(VolPart::Full,IntVector(0,1,0)));
  puzzles.push_back(p2);


  PuzzlePart p3(3);
  p3.parts.push_back(VolPart(VolPart::Full,IntVector(0,0,0)));
  p3.parts.push_back(VolPart(VolPart::Full,IntVector(1,0,0)));
  p3.parts.push_back(VolPart(VolPart::Full,IntVector(1,0,1)));
  p3.parts.push_back(VolPart(VolPart::Full,IntVector(1,1,0)));
  puzzles.push_back(p3);


  PuzzlePart p4(4);
  p4.parts.push_back(VolPart(VolPart::Full,IntVector(1,0,0)));
  p4.parts.push_back(VolPart(VolPart::Full,IntVector(1,1,0)));
  p4.parts.push_back(VolPart(VolPart::Full,IntVector(2,1,0)));
  p4.parts.push_back(VolPart(VolPart::Full,IntVector(0,1,0)));
  puzzles.push_back(p4);


  PuzzlePart p5(5);
  p5.parts.push_back(VolPart(VolPart::Full,IntVector(1,0,0)));
  p5.parts.push_back(VolPart(VolPart::Full,IntVector(1,1,0)));
  p5.parts.push_back(VolPart(VolPart::Full,IntVector(0,1,0)));
  p5.parts.push_back(VolPart(VolPart::Full,IntVector(0,2,0)));
  puzzles.push_back(p5);


  PuzzlePart p6(6);
  p6.parts.push_back(VolPart(VolPart::Full,IntVector(2,0,0)));
  p6.parts.push_back(VolPart(VolPart::Full,IntVector(0,1,0)));
  p6.parts.push_back(VolPart(VolPart::Full,IntVector(1,1,0)));
  p6.parts.push_back(VolPart(VolPart::Full,IntVector(2,1,0)));
  puzzles.push_back(p6);


  PuzzlePart p7(7);
  p7.parts.push_back(VolPart(VolPart::Full,IntVector(1,0,0)));
  p7.parts.push_back(VolPart(VolPart::Full,IntVector(0,1,0)));
  p7.parts.push_back(VolPart(VolPart::Full,IntVector(1,1,0)));
  puzzles.push_back(p7);

  return puzzles;
}

vector<Geometry::PuzzlePart> generateTestPuzzles()
{
  vector<PuzzlePart> puzzles;

  PuzzlePart p1(1);
  p1.parts.push_back(VolPart(VolPart::Full,IntVector(0,0,0)));
  p1.parts.push_back(VolPart(VolPart::Angle,IntVector(0,1,0),IntVector(0,1,-1)));
  puzzles.push_back(p1);

  PuzzlePart p2(2);
  p2.parts.push_back(VolPart(VolPart::Full,IntVector(0,0,0)));
  p2.parts.push_back(VolPart(VolPart::Full,IntVector(0,1,0)));
  p2.parts.push_back(VolPart(VolPart::Full,IntVector(0,0,1)));
  p2.parts.push_back(VolPart(VolPart::Angle,IntVector(0,1,1),IntVector(-1,0,1)));
  puzzles.push_back(p2);


  PuzzlePart p3(3);
  p3.parts.push_back(VolPart(VolPart::Full,IntVector(0,0,0)));
  p3.parts.push_back(VolPart(VolPart::Full,IntVector(0,0,1)));
  p3.parts.push_back(VolPart(VolPart::Angle,IntVector(0,1,0),IntVector(1,1,0)));
  p3.parts.push_back(VolPart(VolPart::Angle,IntVector(1,0,1),IntVector(1,0,-1)));
  puzzles.push_back(p3);

  return puzzles;
}
