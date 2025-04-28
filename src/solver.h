#pragma once

#include <atomic>

#include "geometry.h"
#include "timer.h"
#include "volumepuzzle.h"

namespace Geometry {

class Solver {
  public:
    Solver(VolumePuzzle& puzzle);

    void solve();

    void multithread(bool ml = false);
    void stopSolving();

  private:
    void solveForPiece(int i_puzzle);
    struct Data {
        Data(const Geometry::Box& box) : bbox(box) {}
        Bitset piece_is_placed;
        Box bbox;
        unsigned num_placed = 0;
        PiecesSet solution;
    };
    void remove(Data& data, const Piece& part);
    void place(Data& data, const Piece& part);
    bool couldPlace(Data& data, const Piece& part, bool& matched) const;
    bool hasSqueezed(Data& data, const Piece& part) const;
    bool tryToPlace(Data& data, const Piece& part);

    bool verifyAlgorithm(Data& data);

    bool newSolution();
    bool foundNewSolution(Data& data);
    void recursiveSolve(Data& data);
    void recursiveSolve(Data& data, std::size_t i_puzzle);

  private:
    Timer timer_;
    VolumePuzzle& puzzle_;
    int dim_x_, dim_y_, dim_z_;
    bool continue_to_solve_;
    PiecesSet pieces_;
    unsigned piece_all_positions_number_;
    std::vector<PiecesSet> pieces_in_all_positions_;
    int progress_;
    bool search_all_solutions_;
    std::mutex mutex_;
    std::atomic<int> max_sol_;
};
}  // namespace Geometry
