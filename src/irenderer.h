#pragma once

#include <camera.h>
#include <memory>
#include <sprite.h>
#include <volpart.h>

class IRenderer {
  public:
    virtual ~IRenderer() = default;
    void render(const Geometry::VolPart& vol_part,
                const Geometry::Vector& color);
    virtual void setup() = 0;
    virtual void resize(int w, int h) = 0;

    virtual void startFrame() = 0;
    virtual void finishFrame() = 0;

    Camera& camera() {
        return camera_;
    }

    virtual void drawOverlay(const Sprite& sprite) = 0;

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

  protected:
    Camera camera_;
};

using IRendererPtr = std::shared_ptr<IRenderer>;
