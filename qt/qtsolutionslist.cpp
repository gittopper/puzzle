#include "qtsolutionslist.h"

#include <sstream>

#include "utils.h"

using namespace Geometry;

QTSolutionsList::QTSolutionsList(QWidget* parent) : QListWidget(parent) {
    curItem = -1;
}

void QTSolutionsList::refreshSolutions(VolumePuzzle* puzzle) {
    int i = puzzle->numFoundSolutions();
    clear();

    if (i > 1) {
        std::cout << "Solution number " << i << ":" << std::endl;
        PiecesSet sol;
        puzzle->getSolution(sol, i);
        printLastSolution(sol, puzzle->getEmptyBox());
    }

    for (int k = 1; k <= i; k++) {
        PiecesSet p;
        puzzle->getSolution(p, k);

        std::stringstream ss;
        if (k == 1) {
            ss << "initial puzzles";
        } else {
            ss << "solution" << k << "(" << p.tag() << ")";
        }

        addItem(ss.str().c_str());
    }
    emit solutionSwitched(curItem < 0 ? i : curItem);
}

void QTSolutionsList::showSolution(int i) {
    curItem = i + 1;
    emit solutionSwitched(curItem);
}
