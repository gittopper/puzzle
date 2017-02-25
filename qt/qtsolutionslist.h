#ifndef QTSOLUTIONSLIST_H
#define QTSOLUTIONSLIST_H

#include <QListWidget>
#include "piece.h"
#include "volumepuzzle.h"

class QTSolutionsList : public QListWidget
{
    Q_OBJECT
public:
    explicit QTSolutionsList(QWidget *parent = 0);

signals:
    void solutionSwitched(int i);
public slots:
    void showSolution(int i);
    void refreshSolutions(Geometry::VolumePuzzle* puzzle);
private:
    int curItem;
};

#endif // QTSOLUTIONSLIST_H
