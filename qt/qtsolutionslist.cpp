#include "qtsolutionslist.h"
#include <sstream>

QTSolutionsList::QTSolutionsList(QWidget *parent) :
    QListWidget(parent)
{
    curItem = -1;
}

void QTSolutionsList::refreshSolutions(VolumePuzzle* puzzle)
{
    int i = puzzle->numFoundSolutions();
    clear();
    for(int k = 1; k <= i; k++)
    {
        PiecesSet p;
        puzzle->getSolution(p, k);

        stringstream ss;
        if (k == 1)
        {
            ss << "initial puzzles";
        }
        else
        {
            ss<< "solution" << k << "(";

            for (int k = 0; k < p.size(); k++)
            {
                ss << p.pieces[k].number;
            }
            ss << ")";
        }

        addItem(ss.str().c_str());
    }
    emit solutionSwitched(curItem < 0 ? i : curItem);
}

void QTSolutionsList::showSolution(int i)
{
    curItem = i + 1;
    emit solutionSwitched(curItem);
}
