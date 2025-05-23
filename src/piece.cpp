#include "piece.h"

#include <algorithm>

namespace Geometry {
Piece& Piece::rotate(RotType rot) {
    for (auto& part : parts) {
        part.rotate(rot);
    }
    return *this;
}
Piece& Piece::rotate(Mat rot) {
    for (auto& part : parts) {
        part.rotate(rot);
    }
    return *this;
}
bool Piece::operator==(const Piece& part) const {
    return id == part.id && parts == part.parts;
}
Piece& Piece::shift(const Vector& shift) {
    for (auto& part : parts) {
        part.shift(shift);
    }
    return *this;
}
Mat Piece::getLCS() const {
    Vector x = parts[1].getCoords() - parts[0].getCoords();
    Vector y = parts[2].getCoords() - parts[0].getCoords();
    return Mat(x, y, x.cross(y));
}

Vector Piece::getZero() const {
    return parts[0].getCoords();
}

void Piece::addToBBox(BBox& bbox) const {
    for (auto& part : parts) {
        bbox.merge(part.getCoords());
    }
}
BBox Piece::getBBox() const {
    BBox box;
    addToBBox(box);
    return box;
}

Piece& Piece::centralize() {
    BBox box(getBBox());
    shift(-box.minV());
    return *this;
}
Piece Piece::copy() const {
    return Piece(*this);
}

Mat Piece::getRotationMatrix(const Piece& part) const {
    Mat rot1 = getLCS();
    Mat rot2 = part.getLCS();

    Mat invRot1 = rot1.inverse();
    Mat res = rot2 * invRot1;
    BREAK_ON_LINE(res.det() == 1);
    return res;
}

bool PiecesSet::operator==(const PiecesSet& set) const {
    if (size() != set.size()) {
        return false;
    }
    for (unsigned i = 0; i < size(); i++) {
        if ((*this)[i].id != set[i].id) {
            return false;
        }
    }

    Mat res = (*this)[0].getRotationMatrix(set[0]);

    Vector prevShift = -(*this)[0].getZero();
    Vector shift = set[0].getZero();

    bool theSame = true;

    for (unsigned i = 0; i < set.size(); i++) {
        Piece p = (*this)[i];

        p.shift(prevShift);
        p.rotate(res);
        p.shift(shift);
        theSame = p == set[i];
        if (!theSame) break;
    }

    return theSame;
}

void PiecesSet::rotate(Mat rot) {
    for (std::vector<Piece>::iterator it = begin(); it != end(); ++it) {
        (*it).rotate(rot);
    }
}

bool compNumbers(Piece i, Piece j) {
    return i.id < j.id;
}

void PiecesSet::order() {
    std::sort(begin(), end(), compNumbers);
}

void PiecesSet::shift(Vector v) {
    for (auto& piece : *this) {
        piece.shift(v);
    }
}

std::string PiecesSet::tag() const {
    std::string res;
    for (auto& piece : *this) {
        res += std::to_string(piece.id);
    }
    return res;
}

}  // namespace Geometry
