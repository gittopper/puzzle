#include "mainwindow.h"
#include <QApplication>
#include "utils.h"
#include "qtvolumepuzzle.h"
#include <thread>

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

//    std::auto_ptr<Task> solvingTask(new SolvingTask(puzzle));
//    std::auto_ptr<Thread> solvingThread(new Thread(solvingTask));
//    solvingThread->start();
    Solver solver(dynamic_cast<VolumePuzzle&>(puzzle));
    std::thread solvingThread(solvePuzzle, &solver);

    MainWindow w;
    w.setPuzzleToRender(puzzle);
    w.show();

    int result = a.exec();
//    int solveResult = reinterpret_cast<int>(solvingThread->join());
    solver.stopSolving();
    solvingThread.join();
    return result;
}
