#pragma once
#include <sprite.h>

#include "camera.h"

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

    void drawOverlay(const Sprite& sprite);

  protected:
    void drawLCS();
    Camera camera_;
};
