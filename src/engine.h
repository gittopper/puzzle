#pragma once

#include <desktop/glrenderer.h>

#include <optional>
#include <piecessetrenderer.h>
#include <resourceloader.h>
#include <solver.h>
#include <sprite.h>
#include <thread>
#include <volumepuzzle.h>

class Engine {
  public:
    Engine(Geometry::VolumePuzzle& puzzle,
           IRendererPtr renderer,
           ResourceLoaderPtr resource_loader);
    ~Engine();
    void setup();
    void display();
    void resize(int width, int height);

    void rotateStart(int x, int y);
    void shiftStart(int x, int y);
    void drag(int x, int y);
    void dragStop();
    void zoom(float z);
    void zoomDrag();

    void showSolution(std::size_t i);
    Geometry::VolumePuzzle& puzzle() {
        return puzzle_;
    }

  private:
    Geometry::VolumePuzzle& puzzle_;
    IRendererPtr renderer_;
    PiecesSetRenderer piecesset_renderer_;
    Geometry::Solver solver_;
    std::thread solving_thread_;
    std::size_t cur_sol_ = 0;
    std::size_t max_sol_ = 0;
    std::optional<Sprite> sprite_;
};
