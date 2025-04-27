#pragma once

#include <desktop/glrenderer.h>

#include <engine.h>
#include <utils.h>

class GlutRenderer {
  public:
    GlutRenderer();
    void init(int argc, char** argv);
    void run();

    Engine& engine() {
        return engine_;
    }
    void render();

  private:
    Geometry::VolumePuzzle puzzle_;
    Engine engine_;
    std::size_t num_solutions_ = 0;
};
