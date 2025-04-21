#pragma once

#include "geometry.h"
#include "timer.h"
#include "volumepuzzle.h"
#include <atomic>

namespace Geometry {

struct Data {
    Data(const Geometry::Box& box) : m_box(box) {}
    Bitset m_bs;
    Box m_box;
    unsigned m_numPlaced = 0;
    PiecesSet m_solution;
};
class Solver {
   public:
    Solver(VolumePuzzle& puzzle);

    void solve();

    void multithread(bool ml = false);
    void stopSolving();

   private:
    void solveForPiece(int i_puzzle);
    Timer m_timer;
    VolumePuzzle& m_puzzle;
    int m_dimX, m_dimY, m_dimZ;
    bool m_continue_to_solve;
    PiecesSet m_pieces;
    unsigned m_piece_all_positions_number;
    std::vector<PiecesSet> m_pieces_in_all_positions;
    int m_progress;
    bool m_search_all_solutions;
    std::mutex mutex_;
    std::atomic<int> m_max_sol;

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
};
}  // namespace Geometry
