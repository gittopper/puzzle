#pragma once
#include <irenderer.h>

class GLRenderer : public IRenderer {
  public:
    void setup() override;
    void resize(int w, int h) override;

    void startFrame() override;
    void finishFrame() override;

    void drawOverlay(const Sprite& sprite) override;
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

  protected:
    void drawLCS();
};
