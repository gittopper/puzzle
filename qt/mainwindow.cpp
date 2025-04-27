#include "mainwindow.h"

#include "ui_mainwindow.h"

using namespace Geometry;

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

void MainWindow::setupSignals() {
    auto& puzzle = ui->GLView->puzzle();
    connect(&puzzle, &QTVolumePuzzle::foundSolution, ui->solutions,
            &QTSolutionsList::refreshSolutions);
    connect(ui->solutions, SIGNAL(solutionSwitched(int)), ui->GLView,
            SLOT(renderSolution(int)));
    connect(ui->solutions, SIGNAL(currentRowChanged(int)), ui->solutions,
            SLOT(showSolution(int)));
    puzzle.addedSolution();
}

MainWindow::~MainWindow() {
    delete ui;
}
