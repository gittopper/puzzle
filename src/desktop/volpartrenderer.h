#pragma once
#include <ivolpartrenderer.h>
#include <vector.h>

class VolPartRenderer : public IVolPartRenderer {
  protected:
    void drawSquare(const Geometry::Vector& shift,
                    const Geometry::Vector& v1,
                    const Geometry::Vector& v2,
                    const Geometry::Vector& v3,
                    const Geometry::Vector& v4,
                    const Geometry::Vector& n) const override;

    void drawTriangle(const Geometry::Vector& shift,
                      const Geometry::Vector& v1,
                      const Geometry::Vector& v2,
                      const Geometry::Vector& v3,
                      const Geometry::Vector& n) const override;
    void setColor(const Geometry::Vector& color) const override;
};
