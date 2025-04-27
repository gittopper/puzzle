#include <QApplication>

#include <thread>

#include "mainwindow.h"
#include "qtvolumepuzzle.h"
#include "tests.h"
#include "utils.h"

using namespace Geometry;

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    BREAK_ON_LINE(makeGeneralTests());

    // solve55();

    MainWindow w;
    w.setupSignals();
    w.show();

    int result = a.exec();
    return result;
}
