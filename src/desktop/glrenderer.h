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
    void setPuzzleToRender(Geometry::VolumePuzzle& puzzleToRender);
    virtual ~GLRenderer() {}

    void initOpenGL();
    void display();
    void resize(int w, int h);

    Camera& camera() {
        return camera_;
    }

    void showSolution(std::size_t sol);

  protected:
    void drawLCS();

  private:
    std::size_t cur_sol_;
    std::size_t max_sol_;
    PiecesSetRenderer renderer_;
    virtual void addMenuEntry(int i) {}

    void drawOverlay(const Sprite& sprite);
    const Geometry::VolumePuzzle* puzzle_;

    Camera camera_;
    std::optional<Sprite> sprite_;
};
