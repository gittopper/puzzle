#include "qtvolumepuzzle.h"

void QTVolumePuzzle::addedSolution() {
    emit foundSolution(this);
}
