#include "volumepuzzle.h"

using namespace Geometry;

bool VolumePuzzle::addSolution(const PiecesSet& sol) {
    {
        std::lock_guard<std::mutex> block(lock);
        PiecesSet orderedSolution = sol;
        orderedSolution.order();

        // orderedSolution.shift(-orderedSolution[0].getZero());

        PiecesSet normalizedSolution = orderedSolution;

        Piece part = normalizedSolution[0];
        Piece p = pieces_[part.id - 1];
        p.shift(-p.getZero());

        Mat rotation = part.getRotationMatrix(p);
        BREAK_ON_LINE(rotation.det() == 1);

        normalizedSolution.rotate(rotation);
        normalizedSolution.shift(-normalizedSolution[0].getZero());

        part = normalizedSolution[0];
        BREAK_ON_LINE(part == p);

        for (unsigned iSol = 0; iSol < normalized_solutions_.size(); iSol++) {
            if (normalized_solutions_[iSol] == normalizedSolution) return false;
        }

        solutions_.push_back(orderedSolution);
        normalized_solutions_.push_back(normalizedSolution);
    }
    addedSolution();
    return true;
}

// std::mutex VolumePuzzle::lock;

int VolumePuzzle::numFoundSolutions() const {
    std::lock_guard<std::mutex> block(lock);
    int l = solutions_.size();
    return l;
}

void VolumePuzzle::getSolution(PiecesSet& sol, int i) const {
    std::lock_guard<std::mutex> block(lock);
    assert(i >= 1 && i <= solutions_.size());
    sol = solutions_[i - 1];
}

VolumePuzzle::VolumePuzzle(int xDim,
                           int yDim,
                           int zDim,
                           const PiecesSet puzzlePieces) :
    dim_x_(xDim), dim_y_(yDim), dim_z_(zDim), pieces_(puzzlePieces) {
    PiecesSet c = puzzlePieces;
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
