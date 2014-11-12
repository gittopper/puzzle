#include "geometry.h"
#include "glutrenderer.h"
#include "tests.h"
#include <thread>

using namespace Geometry;

namespace
{
  void solve(VolumePuzzle* puzzle)
  {
    Solver solver(*puzzle);
    solver.solve();
  }
}

int main(int argc, char ** argv)
{
  BREAK_ON_LINE(makeGeneralTests());
  
  //solve55();

  VolumePuzzle puzzle(3, 4, 2, generateWoodPuzzles());
//   Solver VolumePuzzle(2,2,2,generateTestPuzzles());
//   Solver VolumePuzzle(3,3,3,generateSomaPuzzles());

  std::thread st(solve, &puzzle);

//    std::auto_ptr<Task> solvingTask(new SolvingTask(puzzle));
//    std::auto_ptr<Thread> solvingThread(new Thread(solvingTask));
//    solvingThread->start();

  GlutRenderer glutRenderer;

  glutRenderer.init(argc, argv);
  glutRenderer.setPuzzleToRender(puzzle);
  glutRenderer.run();

//  int result = reinterpret_cast<int>(solvingThread->join());
  st.join();

  cout << "Press any key to exit...";
  cin.get();

  return 0;
}