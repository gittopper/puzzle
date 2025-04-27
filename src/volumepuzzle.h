#ifndef volumepuzzle_h__
#define volumepuzzle_h__

#include <mutex>

#include "piece.h"

namespace Geometry {

class VolumePuzzle {
  public:
    VolumePuzzle(int xDim, int yDim, int zDim, const PiecesSet pieces);

    int getXDim() const;
    int getYDim() const;
    int getZDim() const;

    Box getEmptyBox() const;
    const PiecesSet& getPieces() const;

    // true - new solution
    // false - there already exists the same solution
    bool addSolution(const PiecesSet& sol);
    int numFoundSolutions() const;
    void getSolution(PiecesSet& sol, int i) const;

    virtual ~VolumePuzzle() {}

    virtual void addedSolution() {}

  protected:
    std::vector<PiecesSet> solutions_;
    std::vector<PiecesSet> normalized_solutions_;
    int dim_x_, dim_y_, dim_z_;
    mutable std::mutex lock;
    PiecesSet pieces_;

  private:
    VolumePuzzle(const VolumePuzzle&);
};

}  // namespace Geometry

#endif  // volumepuzzle_h__
