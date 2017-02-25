#include "mainwindow.h"
#include <QApplication>
#include "utils.h"
#include "qtvolumepuzzle.h"
#include <thread>
#include "tests.h"

using namespace Geometry;

void solvePuzzle(Solver* solver)
{
    solver->solve();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    BREAK_ON_LINE(makeGeneralTests());

    //solve55();

    QTVolumePuzzle puzzle(3, 4, 2, generateWoodPuzzles());
  //   Solver VolumePuzzle(2,2,2,generateTestPuzzles());
  //   Solver VolumePuzzle(3,3,3,generateSomaPuzzles());

    Solver solver(dynamic_cast<VolumePuzzle&>(puzzle));
    std::thread solvingThread(solvePuzzle, &solver);

    MainWindow w;
    w.setPuzzleToRender(puzzle);
    w.show();

    int result = a.exec();
    solver.stopSolving();
    solvingThread.join();
    return result;
}
