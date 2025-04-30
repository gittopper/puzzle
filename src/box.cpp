#include "box.h"

#include "bbox.h"

namespace Geometry {

Box::Box(int DX, int DY, int DZ) : dim_x_(DX), dim_y_(DY), dim_z_(DZ) {
    for (int i = 0; i < DX; i++) {
        for (int j = 0; j < DY; j++) {
            for (int k = 0; k < DZ; k++) {
                VolPart v = VolPart(VolPart::VolType::Empty, Vector(i, j, k));
                box_.push_back(v);
                BREAK_ON_LINE(getVolPart(i, j, k) == v);
            }
        }
    }
}
bool Box::isSqueezed(const VolPart& vol) const {
    if (vol.type() != VolPart::VolType::Angle) return false;
    BREAK_ON_LINE(!vol.getDir()[0] || !vol.getDir()[1] || !vol.getDir()[2]);
    int n = 0;
    if (vol.getDir()[0] != 0) {
        const VolPart& nvol =
            getVolPart(vol.getCoords()[0] + vol.getDir()[0], vol.getCoords()[1],
                       vol.getCoords()[2]);
        if (nvol.type() == VolPart::VolType::Full) {
            n++;
        } else if (nvol.type() == VolPart::VolType::Angle) {
            if (vol.getDir()[0] * nvol.getDir()[0] >= 0) {
                n++;
            }
        }
    }
    if (vol.getDir()[1] != 0) {
        const VolPart& nvol =
            getVolPart(vol.getCoords()[0], vol.getCoords()[1] + vol.getDir()[1],
                       vol.getCoords()[2]);
        if (nvol.type() == VolPart::VolType::Full) {
            n++;
        } else if (nvol.type() == VolPart::VolType::Angle) {
            if (vol.getDir()[1] * nvol.getDir()[1] >= 0) {
                n++;
            }
        }
    }
    if (vol.getDir()[2] != 0) {
        const VolPart& nvol = getVolPart(vol.getCoords()[0], vol.getCoords()[1],
                                         vol.getCoords()[2] + vol.getDir()[2]);
        if (nvol.type() == VolPart::VolType::Full) {
            n++;
        } else if (nvol.type() == VolPart::VolType::Angle) {
            if (vol.getDir()[2] * nvol.getDir()[2] >= 0) {
                n++;
            }
        }
    }
    return n > 1;
}
bool Box::isSqueezedV2(const VolPart& vol) const {
    if (vol.type() != VolPart::VolType::Angle) {
        return false;
    }

    BREAK_ON_LINE(dot(vol.getDir(), vol.getDir()) == 2);
    int n = 0;
    if (vol.getDir()[0] > 0) {
        const VolPart& nvol = getVolPart(vol.getCoords() + XSHIFT);
        if (nvol.type() == VolPart::VolType::Full || (nvol.hasSide(0, 0))) {
            n++;
        }
    }
    if (vol.getDir()[0] < 0) {
        const VolPart& nvol = getVolPart(vol.getCoords() - XSHIFT);
        if (nvol.type() == VolPart::VolType::Full || nvol.hasSide(0, 1)) {
            n++;
        }
    }

    if (vol.getDir()[1] > 0) {
        const VolPart& nvol = getVolPart(vol.getCoords() + YSHIFT);
        if (nvol.type() == VolPart::VolType::Full || nvol.hasSide(1, 0)) {
            n++;
        }
    }
    if (vol.getDir()[1] < 0) {
        const VolPart& nvol = getVolPart(vol.getCoords() - YSHIFT);
        if (nvol.type() == VolPart::VolType::Full || nvol.hasSide(1, 1)) {
            n++;
        }
    }

    if (vol.getDir()[2] > 0) {
        const VolPart& nvol = getVolPart(vol.getCoords() + ZSHIFT);
        if (nvol.type() == VolPart::VolType::Full || nvol.hasSide(2, 0)) {
            n++;
        }
    }
    if (vol.getDir()[2] < 0) {
        const VolPart& nvol = getVolPart(vol.getCoords() - ZSHIFT);
        if (nvol.type() == VolPart::VolType::Full || nvol.hasSide(2, 1)) {
            n++;
        }
    }

    return n > 1;
}

void Box::add(const std::vector<VolPart>& vols) {
    for (unsigned i = 0; i < vols.size(); i++) {
        getVolPart(vols[i].getCoords()) += vols[i];
    }
}

void Box::rotate(Mat rot) {
    BBox bbox;

    for (int i = 0; i < dim_x_; i++) {
        for (int j = 0; j < dim_y_; j++) {
            for (int k = 0; k < dim_z_; k++) {
                Vector v(i, j, k);
                v = rot * v;
                bbox.merge(v);
            }
        }
    }

    Box new_box(bbox.maxV()[0] - bbox.minV()[0] + 1,
                bbox.maxV()[1] - bbox.minV()[1] + 1,
                bbox.maxV()[2] - bbox.minV()[2] + 1);
    Vector shift(-bbox.minV());

    for (int i = 0; i < dim_x_; ++i) {
        for (int j = 0; j < dim_y_; ++j) {
            for (int k = 0; k < dim_z_; ++k) {
                VolPart new_vol(getVolPart(i, j, k));
                new_vol.rotate(rot).shift(shift);
                const Vector& xyz = new_vol.getCoords();
                new_box.getVolPart(xyz[0], xyz[1], xyz[2]) = new_vol;
            }
        }
    }
    *this = new_box;
}

void Box::remove(const std::vector<VolPart>& vols) {
    for (unsigned i = 0; i < vols.size(); ++i) {
        getVolPart(vols[i].getCoords()) -= vols[i];
    }
}
}  // namespace Geometry
