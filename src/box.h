#pragma once

#include "base.h"
#include "vector.h"
#include "volpart.h"

namespace Geometry {

/// Cubically parted space
class Box {
  public:
    Box(int DX, int DY, int DZ);

    VolPart& getVolPart(const Vector& coords) {
        return getVolPart(coords[0], coords[1], coords[2]);
    }
    /// obtain volume part of space
    VolPart& getVolPart(int x, int y, int z) {
        BREAK_ON_LINE(x < dim_x_ && y < dim_y_ && z < dim_z_);
        auto& val = box_[x * dim_z_ * dim_y_ + y * dim_z_ + z];
        BREAK_ON_LINE(val.getCoords()[0] == x && val.getCoords()[1] == y &&
                      val.getCoords()[2] == z);
        return val;
    }

    int getDimX() const {
        return dim_x_;
    }
    int getDimY() const {
        return dim_y_;
    }
    int getDimZ() const {
        return dim_z_;
    }

    bool isInside(const Vector& coords) const {
        return isInside(coords[0], coords[1], coords[2]);
    }

    bool isInside(int x, int y, int z) const {
        return x < dim_x_ && y < dim_y_ && z < dim_z_;
    }

    const VolPart& getVolPart(const Vector& coords) const {
        return getVolPart(coords[0], coords[1], coords[2]);
    }

    const VolPart& getVolPart(int x, int y, int z) const {
        BREAK_ON_LINE(x < dim_x_ && y < dim_y_ && z < dim_z_);
        const auto& val = box_[x * dim_z_ * dim_y_ + y * dim_z_ + z];
        BREAK_ON_LINE(val.getCoords()[0] == x && val.getCoords()[1] == y &&
                      val.getCoords()[2] == z);
        return val;
    }

    void rotate(Mat rot);

    void add(const std::vector<VolPart>& vols);

    void remove(const std::vector<VolPart>& vols);

    bool isSqueezed(const VolPart& vol) const;

    bool isSqueezedV2(const VolPart& vol) const;

    bool operator==(const Box& b) const {
        return box_ == b.box_;
    }

  private:
    std::vector<VolPart> box_;
    int dim_x_;
    int dim_y_;
    int dim_z_;
};
}  // namespace Geometry
