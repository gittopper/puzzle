#pragma once

#include <QObject>

#include "volumepuzzle.h"

class QTVolumePuzzle : public QObject, public Geometry::VolumePuzzle {
    Q_OBJECT
  public:
    QTVolumePuzzle(int dim_x,
                   int dim_y,
                   int dim_z,
                   const Geometry::PiecesSet pieces) :
        VolumePuzzle(dim_x, dim_y, dim_z, pieces) {}
    void addedSolution();
  signals:
    void foundSolution(VolumePuzzle* puzzle);
};
