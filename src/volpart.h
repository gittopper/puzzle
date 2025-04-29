#pragma once

#include "base.h"
#include "mat.h"
#include "vector.h"

namespace Geometry {
class VolPart {
  public:
    enum class VolType { Empty, Full, Angle };

    VolPart(VolType t, Vector coord, Vector iniDir = Vector(0, 0, 0)) :
        fill_info_(t), xyz_(coord), dir_(iniDir) {}

    bool operator==(const VolPart& vol) const;

    bool hasSide(int dim, int val) const;

    VolPart& operator+=(const VolPart& v);

    VolPart& shift(const Vector& shift);

    VolPart& rotate(RotType rot);

    VolPart& rotate(const Mat& m);

    VolPart& operator-=(const VolPart& another);

    bool couldPlace(const VolPart& another) const;

    bool shareOneOfSides(const VolPart& another) const;

    const Vector& getCoords() const {
        return xyz_;
    }
    void setCoords(const Vector& coords) {
        xyz_ = coords;
    }

    const Vector& getDir() const {
        return dir_;
    }
    void setDir(const Vector& d) {
        dir_ = d;
    }

    VolType type() const {
        return fill_info_;
    }
    void setType(VolType t) {
        fill_info_ = t;
    }

  private:
    VolType fill_info_;
    Vector xyz_, dir_;
};
}  // namespace Geometry
