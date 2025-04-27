#pragma once

#include <desktop/glrenderer.h>

#include <engine.h>
#include <utils.h>

class GlutRenderer {
  public:
    GlutRenderer() :
        puzzle_(3, 4, 2, generateWoodPuzzles()),
        // puzzle_(2,2,2,generateTestPuzzles()),
        // puzzle_(3,3,3,generateSomaPuzzles()),
        engine_(puzzle_, std::make_shared<GLRenderer>()) {}
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
