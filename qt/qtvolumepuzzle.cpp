#include "qtvolumepuzzle.h"

namespace Geometry
{

void QTVolumePuzzle::addedSolution()
{
    emit foundSolution(this);
}

}

