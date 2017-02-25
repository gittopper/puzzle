#ifndef QTVOLUMEPUZZLE_H
#define QTVOLUMEPUZZLE_H

#include "volumepuzzle.h"
#include <QObject>

namespace Geometry
{
class QTVolumePuzzle: public QObject, public VolumePuzzle
{
    Q_OBJECT
public:
    QTVolumePuzzle(int xDim, int yDim, int zDim, const PiecesSet pieces):
        VolumePuzzle(xDim, yDim, zDim, pieces)
    {}
    void addedSolution();
signals:
    void foundSolution(VolumePuzzle* puzzle);
};

}
#endif // QTVOLUMEPUZZLE_H
