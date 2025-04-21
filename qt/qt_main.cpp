#include "mainwindow.h"
#include <QApplication>
#include "utils.h"
#include "qtvolumepuzzle.h"
#include <thread>
#include "tests.h"

using namespace Geometry;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    BREAK_ON_LINE(makeGeneralTests());

    //solve55();

    QTVolumePuzzle puzzle(3, 4, 2, generateWoodPuzzles());
  //   Solver VolumePuzzle(2,2,2,generateTestPuzzles());
  //   Solver VolumePuzzle(3,3,3,generateSomaPuzzles());

    Solver solver(dynamic_cast<VolumePuzzle&>(puzzle));
    std::thread solving_thread([&solver](){
        solver.solve();
    });

    MainWindow w;
    w.setPuzzleToRender(puzzle);
    w.show();

    int result = a.exec();
    solver.stopSolving();
    solving_thread.join();
    return result;
}
