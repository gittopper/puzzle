#include "volpart.h"

namespace Geometry {
bool VolPart::operator==(const VolPart& vol) const {
    return xyz_ == vol.xyz_ && fill_info_ == vol.fill_info_ &&
           (fill_info_ != VolType::Angle || dir_ == vol.dir_);
}

bool VolPart::hasSide(int dim, int val) const {
    if (fill_info_ == VolType::Empty) {
        return false;
    }
    if (fill_info_ == VolType::Full) {
        return true;
    }
    BREAK_ON_LINE(!dir_[dim] || dir_[dim] * dir_[dim] == 1);
    return dir_[dim] * (1 - 2 * val) >= 0;
}

VolPart& VolPart::shift(const Vector& shift) {
    xyz_ += shift;
    return *this;
}

VolPart& VolPart::operator+=(const VolPart& v) {
    BREAK_ON_LINE(xyz_ == v.xyz_);
    if (fill_info_ == VolType::Empty) {
        fill_info_ = v.fill_info_;
        dir_ = v.dir_;
        return *this;
    }
    if (fill_info_ == VolType::Angle && v.fill_info_ == VolType::Angle &&
        dir_ == -v.dir_) {
        fill_info_ = VolType::Full;
        return *this;
    }
    BREAK_ON_LINE(false);
    return *this;
}

VolPart& VolPart::rotate(RotType rot) {
    BREAK_ON_LINE(fill_info_ != VolType::Empty);
    xyz_.rotate(rot);
    if (fill_info_ == VolType::Angle) {
        dir_.rotate(rot);
    }
    return *this;
}

VolPart& VolPart::rotate(const Mat& m) {
    xyz_ = m * xyz_;
    if (fill_info_ == VolType::Angle) {
        dir_ = m * dir_;
    }
    return *this;
}

VolPart& VolPart::operator-=(const VolPart& another) {
    if (fill_info_ == VolType::Full) {
        if (another.fill_info_ == VolType::Full) {
            fill_info_ = VolType::Empty;
            return *this;
        } else if (another.fill_info_ == VolType::Angle) {
            fill_info_ = VolType::Angle;
            dir_ = -another.dir_;
            return *this;
        } else {
            BREAK_ON_LINE(false);
        }
    }
    if (fill_info_ == VolType::Angle) {
        if (another.fill_info_ == VolType::Angle && dir_ == another.dir_) {
            fill_info_ = VolType::Empty;
            return *this;
        } else {
            BREAK_ON_LINE(false);
        }
    }
    return *this;
}
bool VolPart::couldPlace(const VolPart& another) const {
    BREAK_ON_LINE(xyz_ == another.xyz_);
    BREAK_ON_LINE(another.fill_info_ != VolType::Empty);
    return fill_info_ == VolType::Empty ||
           fill_info_ == VolType::Angle &&
               another.fill_info_ == VolType::Angle && dir_ == -another.dir_ ||
           fill_info_ == VolType::Full && another.fill_info_ == VolType::Empty;
}
bool VolPart::shareOneOfSides(const VolPart& another) const {
    BREAK_ON_LINE(dot(xyz_ - another.xyz_, xyz_ - another.xyz_) <= 1);

    if (fill_info_ == VolType::Empty || another.fill_info_ == VolType::Empty) {
        return false;
    }
    if (fill_info_ == VolType::Full && another.fill_info_ == VolType::Full) {
        return true;
    }
    if (fill_info_ == VolType::Angle && another.fill_info_ == VolType::Full) {
        return dot(dir_, another.xyz_ - xyz_) < 0;
    }
    if (fill_info_ == VolType::Full && another.fill_info_ == VolType::Angle) {
        return dot(another.dir_, xyz_ - another.xyz_) < 0;
    }
    if (fill_info_ == VolType::Angle && another.fill_info_ == VolType::Angle) {
        // return true;
        if (xyz_ == another.xyz_) {
            if (dir_ == -another.dir_) {
                return true;
            }
            BREAK_ON_LINE(false);
        } else {
            return dot(dir_, another.xyz_ - xyz_) < 0 &&
                   dot(another.dir_, xyz_ - another.xyz_) < 0;
        }
    }
    BREAK_ON_LINE(false);
    return false;
}
}  // namespace Geometry
