#pragma once
#include <optional>
#include <piecessetrenderer.h>
#include <sprite.h>

#include "base.h"
#include "camera.h"
#include "piece.h"
#include "utils.h"
#include "volumepuzzle.h"

class GLRenderer {
  public:
    GLRenderer();

    void setup();
    void resize(int w, int h);

    void startFrame();
    void finishFrame();

    Camera& camera() {
        return camera_;
    }

  protected:
    void drawLCS();

  private:
    void drawOverlay(const Sprite& sprite);

    Camera camera_;
    std::optional<Sprite> sprite_;
};
