#pragma once

#include "base.h"
#include "vector.h"

namespace Geometry {
class BBox {
  public:
    BBox() : min_v_(1000, 1000, 1000), max_v_(-1000, -1000, -1000) {}
    void merge(const Vector& v) {
        min_v_[0] = min_v_[0] > v[0] ? v[0] : min_v_[0];
        min_v_[1] = min_v_[1] > v[1] ? v[1] : min_v_[1];
        min_v_[2] = min_v_[2] > v[2] ? v[2] : min_v_[2];

        max_v_[0] = max_v_[0] < v[0] ? v[0] : max_v_[0];
        max_v_[1] = max_v_[1] < v[1] ? v[1] : max_v_[1];
        max_v_[2] = max_v_[2] < v[2] ? v[2] : max_v_[2];
    }
    void grow() {
        min_v_ = min_v_ - Vector(1, 1, 1);
        max_v_ = max_v_ + Vector(1, 1, 1);
    }

    int getXSize() const {
        return max_v_[0] - min_v_[0];
    }
    int getYSize() const {
        return max_v_[1] - min_v_[1];
    }
    int getZSize() const {
        return max_v_[2] - min_v_[2];
    }

    const Vector& minV() const {
        return min_v_;
    }
    const Vector& maxV() const {
        return max_v_;
    }

  private:
    Vector min_v_, max_v_;
};
}  // namespace Geometry
