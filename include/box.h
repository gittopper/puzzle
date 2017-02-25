#pragma once

#include "base.h"
#include "vector.h"
#include "volpart.h"



namespace Geometry
{

///Cubically parted space
class Box
{
public:
    Box(int DX, int DY, int DZ);

    VolPart& getVolPart(const Vector& coords)
    {
        return getVolPart(coords[0], coords[1], coords[2]);
    }
    ///obtain volume part of space
    VolPart& getVolPart(int x, int y, int z)
    {
        BREAK_ON_LINE(x < dimX || y < dimY || z < dimZ);
        return box[x * dimZ * dimY + y * dimZ + z];
    }

    int getDimX() const
    {
        return dimX;
    }
    int getDimY() const
    {
        return dimY;
    }
    int getDimZ() const
    {
        return dimZ;
    }

    const VolPart& getVolPart(const Vector& coords) const
    {
        return getVolPart(coords[0], coords[1], coords[2]);
    }

    const VolPart& getVolPart(int x, int y, int z) const
    {
        return box[x * dimZ * dimY + y * dimZ + z];
    }

    void rotate(Mat rot);

    void add(const std::vector<VolPart>& vols);

    void remove(const std::vector<VolPart>& vols);

    bool isSqueezed(const VolPart& vol) const;

    bool isSqueezedV2(const VolPart& vol) const;

    bool operator == (const Box& b) const
    {
        return box == b.box;
    }
private:
    std::vector<VolPart> box;
    int dimX, dimY, dimZ;
};
}
