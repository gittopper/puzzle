#include "volumepuzzle.h"

#include <logger.hpp>
#include <timer.h>

using namespace Geometry;

bool VolumePuzzle::addSolution(const PiecesSet& sol) {
    {
        std::lock_guard<std::mutex> lock(mutex_);
        PiecesSet ordered_solution = sol;
        ordered_solution.order();

        // ordered_solution.shift(-ordered_solution[0].getZero());

        PiecesSet normalized_solution = ordered_solution;

        Piece part = normalized_solution[0];
        Piece p = pieces_[part.id - 1];
        p.shift(-p.getZero());

        Mat rotation = part.getRotationMatrix(p);
        BREAK_ON_LINE(rotation.det() == 1);

        normalized_solution.rotate(rotation);
        normalized_solution.shift(-normalized_solution[0].getZero());

        part = normalized_solution[0];
        BREAK_ON_LINE(part == p);

        for (unsigned iSol = 0; iSol < normalized_solutions_.size(); iSol++) {
            if (normalized_solutions_[iSol] == normalized_solution)
                return false;
        }

        solutions_.push_back(ordered_solution);
        normalized_solutions_.push_back(normalized_solution);
    }
    LOGI("added solution");
    addedSolution();
    return true;
}

int VolumePuzzle::numFoundSolutions() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return solutions_.size();
}

void VolumePuzzle::getSolution(PiecesSet& sol, int i) const {
    std::lock_guard<std::mutex> lock(mutex_);
    assert(i >= 1 && i <= solutions_.size());
    sol = solutions_[i - 1];
}

VolumePuzzle::VolumePuzzle(int xDim,
                           int yDim,
                           int zDim,
                           const PiecesSet puzzle_pieces) :
    dim_x_(xDim), dim_y_(yDim), dim_z_(zDim), pieces_(puzzle_pieces) {
    PiecesSet c = puzzle_pieces;
    for (int i = 0; i < c.size(); i++) {
        c[i].shift(Vector(2 * i, 0, 0));
    }
    addSolution(c);  // for debug
}

int VolumePuzzle::getXDim() const {
    return dim_x_;
}

int VolumePuzzle::getYDim() const {
    return dim_y_;
}

int VolumePuzzle::getZDim() const {
    return dim_z_;
}

const Geometry::PiecesSet& VolumePuzzle::getPieces() const {
    return pieces_;
}

Geometry::Box VolumePuzzle::getEmptyBox() const {
    Box cleanBox(dim_x_ + 2, dim_y_ + 2, dim_z_ + 2);

    for (int x = 0; x < dim_x_ + 2; x++) {
        for (int y = 0; y < dim_y_ + 2; y++) {
            for (int z = 0; z < dim_z_ + 2; z++) {
                bool isWall = !(x % (dim_x_ + 1)) || !(y % (dim_y_ + 1)) ||
                              !(z % (dim_z_ + 1));
                if (isWall) {
                    cleanBox.getVolPart(x, y, z) =
                        VolPart(isWall ? VolPart::VolType::Full
                                       : VolPart::VolType::Empty,
                                Vector(x, y, z), Vector(0, 0, 0));
                }
            }
        }
    }
    return cleanBox;
}
