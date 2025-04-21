#include "solver.h"

#include <thread>

#include "volpartrenderer.h"
#include "utils.h"

namespace Geometry {
Solver::Solver(VolumePuzzle& puzzleInstance)
    : m_continue_to_solve(true),
      m_max_sol(0),
      m_progress(0),
      m_search_all_solutions(true),
      m_puzzle(puzzleInstance),
      m_dimX(m_puzzle.getXDim()),
      m_dimY(m_puzzle.getYDim()),
      m_dimZ(m_puzzle.getZDim()) {
    m_pieces = m_puzzle.getPieces();
    for (unsigned pn = 0; pn < m_pieces.size(); pn++) {
        m_piece_all_positions_number = 0;
        const Piece& piece = m_pieces[pn];
        Piece copy0 = piece;
        PiecesSet one_piece_all_positions;
        std::vector<BBox> piecesBoxes;
        for (int k = 0; k < 4; k++) {
            copy0.rotate(RotateX);
            auto copy1 = copy0;
            for (int i = 0; i < 4; i++) {
                copy1.rotate(RotateY);

                Piece copy2 = copy1;
                for (int j = 0; j < 4; j++) {
                    BBox box = copy2.rotate(RotateZ).getBBox();
                    copy2.shift(-box.minV);

                    if (m_dimX - box.getXSize() < 1 ||
                        m_dimY - box.getYSize() < 1 ||
                        m_dimZ - box.getZSize() < 1)
                        continue;

                    for (const Piece& p : one_piece_all_positions) {
                        if (p == copy2) continue;
                    }
                    one_piece_all_positions.push_back(copy2);
                    piecesBoxes.push_back(box);
                }
            }
        }
        m_piece_all_positions_number += one_piece_all_positions.size();
        m_pieces_in_all_positions.push_back(one_piece_all_positions);
    }
}

void Solver::remove(Data& data, const Piece& part) {
    data.m_box.remove(part.parts);
    data.m_numPlaced--;
}

void Solver::place(Data& data, const Piece& part) {
    data.m_box.add(part.parts);
    data.m_numPlaced++;
    return;
}

bool Solver::couldPlace(Data& data, const Piece& part, bool& matched) const {
    matched = true;
    for (unsigned i = 0; i < part.parts.size(); i++) {
        const VolPart& vol = part.parts[i];
        if (!data.m_box.isInside(vol.getCoords()) ||
            !data.m_box.getVolPart(vol.getCoords()).couldPlace(vol)) {
            return false;
        }

        continue;

        if (matched) {
            continue;
        }
        matched = matched ||
                  data.m_box.getVolPart(vol.getCoords()).shareOneOfSides(vol);
        if (matched) {
            continue;
        }

        matched = matched || data.m_box.getVolPart(vol.getCoords() - XSHIFT)
                                 .shareOneOfSides(vol);
        if (matched) {
            continue;
        }

        matched = matched || data.m_box.getVolPart(vol.getCoords() + XSHIFT)
                                 .shareOneOfSides(vol);
        if (matched) {
            continue;
        }

        matched = matched || data.m_box.getVolPart(vol.getCoords() - YSHIFT)
                                 .shareOneOfSides(vol);
        if (matched) {
            continue;
        }

        matched = matched || data.m_box.getVolPart(vol.getCoords() + YSHIFT)
                                 .shareOneOfSides(vol);
        if (matched) {
            continue;
        }

        matched = matched || data.m_box.getVolPart(vol.getCoords() - ZSHIFT)
                                 .shareOneOfSides(vol);
        if (matched) {
            continue;
        }

        matched = matched || data.m_box.getVolPart(vol.getCoords() + ZSHIFT)
                                 .shareOneOfSides(vol);
    }

    return true;
}

bool Solver::hasSqueezed(Data& data, const Piece& part) const {
    return false;
    BBox bbox;
    part.addToBBox(bbox);
    bbox.grow();

    for (int x = bbox.minV[0]; x <= bbox.maxV[0]; x++) {
        for (int y = bbox.minV[1]; y <= bbox.maxV[1]; y++) {
            for (int z = bbox.minV[2]; z <= bbox.maxV[2]; z++) {
                //          if (isSqueezed(box.getVolPart(x, y, z])) return
                //          true;
                BREAK_ON_LINE(
                    data.m_box.isSqueezed(data.m_box.getVolPart(x, y, z)) ==
                    data.m_box.isSqueezedV2(data.m_box.getVolPart(x, y, z)));
                if (data.m_box.isSqueezedV2(data.m_box.getVolPart(x, y, z))) {
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

    if (data.m_numPlaced && !matched) {
        return false;
    }

    place(data, part);

    //    if (hasSqueezed(data, part)) {
    //        remove(data, part);
    //        return false;
    //    }

    return true;
}

bool Solver::verifyAlgorithm(Data& data) {
    Box tt = m_puzzle.getEmptyBox();

    for (unsigned i = 0; i < data.m_solution.size(); i++) {
        tt.add(data.m_solution[i].parts);
    }

    return tt == data.m_box;
}

bool Solver::foundNewSolution(Data& data) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (m_puzzle.addSolution(data.m_solution)) {
        m_max_sol = data.m_numPlaced;
        return true;
    }

    return false;
}

void Solver::multithread(bool ml) {}

void Solver::stopSolving() { m_continue_to_solve = false; }

void Solver::solveForPiece(int i_puzzle) {
    Data data(m_puzzle.getEmptyBox());
    data.m_bs.resize(m_pieces.size(), true);
    data.m_bs[i_puzzle] = false;

    const PiecesSet& piece_all_positions = m_pieces_in_all_positions[i_puzzle];
    for (unsigned i = 0; i < piece_all_positions.size(); i++) {
        Piece curPiece = piece_all_positions[i];
        const BBox boundaries = curPiece.getBBox();

        int xmax = m_dimX - boundaries.getXSize();
        int ymax = m_dimY - boundaries.getYSize();
        int zmax = m_dimZ - boundaries.getZSize();

        if (data.m_numPlaced == 0) {
            xmax = std::min(xmax, xmax / 2 + 1);
            ymax = std::min(ymax, ymax / 2 + 1);
            zmax = std::min(zmax, zmax / 2 + 1);
        }

        for (int x = 1; x <= xmax; x++) {
            for (int y = 1; y <= ymax; y++) {
                for (int z = 1; z <= zmax; z++) {
                    if (!m_continue_to_solve) {
                        return;
                    }

                    Vector s(x, y, z);
                    curPiece.shift(s);

                    if (tryToPlace(data, curPiece)) {
                        data.m_solution.push_back(curPiece);
                        recursiveSolve(data);
                        remove(data, curPiece);
                        data.m_solution.pop_back();
                    }
                    curPiece.shift(-s);
                }
            }
        }
        std::cout << "Progress:"
                  << (float(++m_progress) / m_piece_all_positions_number)
                  << std::endl;
        std::cout << "Elapsed time:" << m_timer.asString() << std::endl;
    }
    data.m_bs[i_puzzle] = true;
}

void Solver::solve() {
    std::cout << "starting to solve puzzle" << std::endl;
    m_timer.start();
    std::vector<std::thread> threads;
    auto num_threads = m_pieces.size() / 2;
    for (auto i_thread = 0UL; i_thread < num_threads; ++i_thread) {
        std::cout << "starting " << i_thread << " thread" << std::endl;
//        threads.push_back(std::thread([this, i_thread](){
        solveForPiece(2* i_thread);
        solveForPiece(2* i_thread + 1);
        //}));
    }
    for (auto& t : threads) {
        t.join();
    }
    m_timer.stop();
    std::cout << "solved" << std::endl;
    std::cout << getLogString("finish time: ", m_timer.time()) << std::endl;
}

void Solver::recursiveSolve(Data& data) {
    BREAK_ON_LINE(verifyAlgorithm(data));

    if (m_max_sol < data.m_numPlaced) {
        foundNewSolution(data);
    }

    if (data.m_numPlaced == m_pieces.size()) {
        foundNewSolution(data);
        return;
    }
    for (unsigned iPuzzle = 0; iPuzzle < m_pieces.size(); iPuzzle++) {
        if (!data.m_bs[iPuzzle]) {
            continue;
        }

        data.m_bs[iPuzzle] = false;

        PiecesSet& piece_all_positions = m_pieces_in_all_positions[iPuzzle];
        for (unsigned i = 0; i < piece_all_positions.size(); i++) {
            Piece curPiece = piece_all_positions[i];
            const BBox boundaries = curPiece.getBBox();

            int xmax = m_dimX - boundaries.getXSize();
            int ymax = m_dimY - boundaries.getYSize();
            int zmax = m_dimZ - boundaries.getZSize();

            if (data.m_numPlaced == 0) {
                xmax = std::min(xmax, xmax / 2 + 1);
                ymax = std::min(ymax, ymax / 2 + 1);
                zmax = std::min(zmax, zmax / 2 + 1);
            }

            for (int x = 1; x <= xmax; x++) {
                for (int y = 1; y <= ymax; y++) {
                    for (int z = 1; z <= zmax; z++) {
                        if (!m_continue_to_solve) {
                            return;
                        }

                        Vector s(x, y, z);
                        curPiece.shift(s);

                        if (tryToPlace(data, curPiece)) {
                            data.m_solution.push_back(curPiece);
                            recursiveSolve(data);
                            remove(data, curPiece);
                            data.m_solution.pop_back();
                        }
                        curPiece.shift(-s);
                    }
                }
            }
        }
        data.m_bs[iPuzzle] = true;
    }
}
}  // namespace Geometry
