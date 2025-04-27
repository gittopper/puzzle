#pragma once
#include <optional>
#include <piecessetrenderer.h>
#include <sprite.h>

#include "base.h"
#include "camera.h"
#include "piece.h"
#include "utils.h"
#include "volumepuzzle.h"

namespace Geometry {
class GLRenderer {
  public:
    GLRenderer();
    void setPuzzleToRender(VolumePuzzle& puzzleToRender);
    virtual ~GLRenderer() {}

  protected:
    void initOpenGL();
    void display();
    void drawLCS();
    void resize(int w, int h);

    void mouseMove(int x, int y);

    void mouseLButtonDown(int x, int y);
    void mouseLButtonUp(int x, int y);

    void mouseRButtonDown(int x, int y);
    void mouseRButtonUp(int x, int y);

    void wheelUp(int x, int y);
    void wheelDown(int x, int y);

    void showSolution(int sol);

  private:
    int cur_sol_;
    int max_sol_;
    PiecesSetRenderer renderer_;
    virtual void addMenuEntry(int i) {}

    void drawOverlay(const Sprite& sprite);
    const VolumePuzzle* puzzle_;

    Camera camera_;
    std::optional<Sprite> sprite_;
};

}  // namespace Geometry
