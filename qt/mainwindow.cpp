#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::setPuzzleToRender(QTVolumePuzzle& puzzleToRender)
{
    ui->GLView->setPuzzleToRender(puzzleToRender);
    connect(&puzzleToRender, SIGNAL(foundSolution(VolumePuzzle*)), ui->solutions, SLOT(refreshSolutions(VolumePuzzle*)));
    connect(ui->solutions, SIGNAL(solutionSwitched(int)), ui->GLView, SLOT(renderSolution(int)));
    connect(ui->solutions, SIGNAL(currentRowChanged(int)), ui->solutions, SLOT(showSolution(int)));
    puzzleToRender.addedSolution();
}

MainWindow::~MainWindow()
{
    delete ui;
}
