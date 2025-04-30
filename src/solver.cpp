#include "solver.h"

#include <logger.hpp>
#include <thread>

#include "utils.h"

namespace Geometry {
Solver::Solver(VolumePuzzle& puzzle) :
    continue_to_solve_(true),
    max_sol_(0),
    progress_(0),
    search_all_solutions_(true),
    multithread_(true),
    puzzle_(puzzle),
    dim_x_(puzzle_.getXDim()),
    dim_y_(puzzle_.getYDim()),
    dim_z_(puzzle_.getZDim()) {
    pieces_ = puzzle_.getPieces();
    for (unsigned pn = 0; pn < pieces_.size(); pn++) {
        pieces_all_positions_number_ = 0;
        const Piece& piece = pieces_[pn];
        Piece copy0 = piece;
        PiecesSet one_piece_all_positions;
        std::vector<BBox> pieces_boxes;
        for (int k = 0; k < 4; k++) {
            copy0.rotate(RotateX);
            auto copy1 = copy0;
            for (int i = 0; i < 4; i++) {
                copy1.rotate(RotateY);

                Piece copy2 = copy1;
                for (int j = 0; j < 4; j++) {
                    BBox box = copy2.rotate(RotateZ).getBBox();
                    copy2.shift(-box.minV());

                    if (dim_x_ - box.getXSize() < 1 ||
                        dim_y_ - box.getYSize() < 1 ||
                        dim_z_ - box.getZSize() < 1)
                        continue;

                    for (const Piece& p : one_piece_all_positions) {
                        if (p == copy2) {
                            continue;
                        }
                    }
                    one_piece_all_positions.push_back(copy2);
                    pieces_boxes.push_back(box);
                }
            }
        }
        pieces_all_positions_number_ += one_piece_all_positions.size();
        pieces_in_all_positions_.push_back(one_piece_all_positions);
    }
}

void Solver::remove(Data& data, const Piece& part) {
    data.bbox.remove(part.parts);
    data.num_placed--;
}

void Solver::place(Data& data, const Piece& part) {
    data.bbox.add(part.parts);
    data.num_placed++;
    return;
}

bool Solver::couldPlace(Data& data, const Piece& part, bool& matched) const {
    matched = false;
    for (unsigned i = 0; i < part.parts.size(); i++) {
        const VolPart& vol = part.parts[i];
        if (!data.bbox.isInside(vol.getCoords()) ||
            !data.bbox.getVolPart(vol.getCoords()).couldPlace(vol)) {
            return false;
        }

        if (matched) {
            continue;
        }
        matched = matched ||
                  data.bbox.getVolPart(vol.getCoords()).shareOneOfSides(vol);
        if (matched) {
            continue;
        }

        matched =
            matched ||
            data.bbox.getVolPart(vol.getCoords() - XSHIFT).shareOneOfSides(vol);
        if (matched) {
            continue;
        }

        matched =
            matched ||
            data.bbox.getVolPart(vol.getCoords() + XSHIFT).shareOneOfSides(vol);
        if (matched) {
            continue;
        }

        matched =
            matched ||
            data.bbox.getVolPart(vol.getCoords() - YSHIFT).shareOneOfSides(vol);
        if (matched) {
            continue;
        }

        matched =
            matched ||
            data.bbox.getVolPart(vol.getCoords() + YSHIFT).shareOneOfSides(vol);
        if (matched) {
            continue;
        }

        matched =
            matched ||
            data.bbox.getVolPart(vol.getCoords() - ZSHIFT).shareOneOfSides(vol);
        if (matched) {
            continue;
        }

        matched =
            matched ||
            data.bbox.getVolPart(vol.getCoords() + ZSHIFT).shareOneOfSides(vol);
    }

    return true;
}

bool Solver::hasSqueezed(Data& data, const Piece& part) const {
    return false;
    BBox bbox;
    part.addToBBox(bbox);
    bbox.grow();

    for (int x = bbox.minV()[0]; x <= bbox.maxV()[0]; x++) {
        for (int y = bbox.minV()[1]; y <= bbox.maxV()[1]; y++) {
            for (int z = bbox.minV()[2]; z <= bbox.maxV()[2]; z++) {
                BREAK_ON_LINE(
                    data.bbox.isSqueezed(data.bbox.getVolPart(x, y, z)) ==
                    data.bbox.isSqueezedV2(data.bbox.getVolPart(x, y, z)));
                if (data.bbox.isSqueezedV2(data.bbox.getVolPart(x, y, z))) {
                    return true;
                }
            }
        }
    }

    return false;
}

bool Solver::tryToPlace(Data& data, const Piece& part) {
    bool matched;

    if (!couldPlace(data, part, matched)) {
        return false;
    }

    if (data.num_placed && !matched) {
        return false;
    }

    place(data, part);

    if (hasSqueezed(data, part)) {
        remove(data, part);
        return false;
    }

    return true;
}

bool Solver::verifyAlgorithm(Data& data) {
    Box tt = puzzle_.getEmptyBox();

    for (unsigned i = 0; i < data.solution.size(); i++) {
        tt.add(data.solution[i].parts);
    }

    return tt == data.bbox;
}

bool Solver::foundNewSolution(Data& data) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (max_sol_ >= data.num_placed) {
        return false;
    }
    if (puzzle_.addSolution(data.solution)) {
        max_sol_ = data.num_placed;
        return true;
    }

    return false;
}

void Solver::solveForPiece(int i_puzzle) {
    Data data(puzzle_.getEmptyBox());
    data.piece_is_available.resize(pieces_.size(), true);
    data.piece_is_available[i_puzzle] = false;

    recursiveSolve(data, i_puzzle);
}

void Solver::recursiveSolve(Data& data) {
    BREAK_ON_LINE(verifyAlgorithm(data));

    if (max_sol_ < data.num_placed) {
        foundNewSolution(data);
    }

    if (data.num_placed == pieces_.size()) {
        foundNewSolution(data);
        return;
    }
    for (unsigned i_puzzle = 0; i_puzzle < pieces_.size(); i_puzzle++) {
        if (!data.piece_is_available[i_puzzle]) {
            continue;
        }
        recursiveSolve(data, i_puzzle);
    }
}

void Solver::recursiveSolve(Data& data, std::size_t i_puzzle) {
    data.piece_is_available[i_puzzle] = false;
    PiecesSet& piece_all_positions = pieces_in_all_positions_[i_puzzle];
    for (unsigned i = 0; i < piece_all_positions.size(); ++i) {
        if (data.num_placed == 0) {
            LOGI("Progress:",
                 int(10000 * float(++progress_) / pieces_all_positions_number_) /
                     100.,
                 "%");
            LOGI("Elapsed time:", timer_.elapsedAsString());
        }
        Piece cur_piece = piece_all_positions[i];
        const BBox boundaries = cur_piece.getBBox();

        int xmax = dim_x_ - boundaries.getXSize();
        int ymax = dim_y_ - boundaries.getYSize();
        int zmax = dim_z_ - boundaries.getZSize();
        if (data.num_placed == 0) {
            xmax = std::min(xmax, xmax / 2 + 1);
            ymax = std::min(ymax, ymax / 2 + 1);
            zmax = std::min(zmax, zmax / 2 + 1);
        }

        for (int x = 1; x <= xmax; x++) {
            for (int y = 1; y <= ymax; y++) {
                for (int z = 1; z <= zmax; z++) {
                    if (!continue_to_solve_) {
                        return;
                    }

                    Vector s(x, y, z);
                    cur_piece.shift(s);

                    if (tryToPlace(data, cur_piece)) {
                        data.solution.push_back(cur_piece);
                        recursiveSolve(data);
                        remove(data, cur_piece);
                        data.solution.pop_back();
                    }
                    cur_piece.shift(-s);
                }
            }
        }
    }
    data.piece_is_available[i_puzzle] = true;
}

void Solver::stopSolving() {
    continue_to_solve_ = false;
}

void Solver::solve() {
    if (multithread_) {
        solveMultithread();
    } else {
        solveOneThread();
    }
}

void Solver::solveOneThread() {
    LOGI("starting to solve puzzle");
    timer_.start();
    for (auto i_piece = 0UL; i_piece < pieces_.size(); ++i_piece) {
        LOGI("starting to solve piece ", i_piece);
        solveForPiece(i_piece);
    }
    timer_.stop();
    LOGI("solved!");
    LOGI("elapsed time: ", timer_.elapsedAsString());
}

void Solver::solveMultithread() {
    LOGI("starting to solve puzzle");
    timer_.start();
    std::vector<std::thread> threads;
    auto num_threads = pieces_.size();
    for (auto i_thread = 0UL; i_thread < num_threads; ++i_thread) {
        LOGI("starting ", i_thread, " thread");
        threads.push_back(std::thread([this, i_thread]() {
            solveForPiece(i_thread);
        }));
    }
    for (auto& t : threads) {
        t.join();
    }
    timer_.stop();
    LOGI("solved!");
    LOGI("elapsed time: ", timer_.elapsedAsString());
}

}  // namespace Geometry
