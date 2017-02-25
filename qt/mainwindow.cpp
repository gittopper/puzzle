#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace Geometry;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::setPuzzleToRender(Geometry::QTVolumePuzzle& puzzleToRender)
{
    ui->GLView->setPuzzleToRender(puzzleToRender);
    connect(&puzzleToRender, &QTVolumePuzzle::foundSolution, ui->solutions, &QTSolutionsList::refreshSolutions);
    connect(ui->solutions, SIGNAL(solutionSwitched(int)), ui->GLView, SLOT(renderSolution(int)));
    connect(ui->solutions, SIGNAL(currentRowChanged(int)), ui->solutions, SLOT(showSolution(int)));
    puzzleToRender.addedSolution();
}

MainWindow::~MainWindow()
{
    delete ui;
}
