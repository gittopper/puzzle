#pragma once
#include "base.h"
#include "piece.h"
#include "utils.h"
#include "volumepuzzle.h"
#include "camera.h"
#include <sprite.h>
#include <optional>

namespace Geometry
{
class GLRenderer
{
public:
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
    int curSol, maxSol;
    virtual void addMenuEntry(int i) {}

    void drawOverlay(const Sprite& sprite);
    const VolumePuzzle* puzzle;

    int lastX, lastY;
    std::vector<Vector> colors;
    Camera camera;
    std::optional<Sprite> sprite_;
};

}
