#pragma once

#include <memory>
#include <volpart.h>

class IVolPartRenderer {
  public:
    virtual ~IVolPartRenderer() = default;
    void render(const Geometry::VolPart& vol_part,
                const Geometry::Vector& color);

  protected:
    virtual void drawSquare(const Geometry::Vector& shift,
                            const Geometry::Vector& v1,
                            const Geometry::Vector& v2,
                            const Geometry::Vector& v3,
                            const Geometry::Vector& v4,
                            const Geometry::Vector& n) const = 0;

    virtual void drawTriangle(const Geometry::Vector& shift,
                              const Geometry::Vector& v1,
                              const Geometry::Vector& v2,
                              const Geometry::Vector& v3,
                              const Geometry::Vector& n) const = 0;
    virtual void setColor(const Geometry::Vector& color) const = 0;
};

using IVolPartRendererPtr = std::shared_ptr<IVolPartRenderer>;
