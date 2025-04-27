#pragma once

#include <desktop/glrenderer.h>

#include <solver.h>
#include <thread>
#include <volumepuzzle.h>

class Engine {
  public:
    Engine(Geometry::VolumePuzzle& puzzle);
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
    GLRenderer renderer_;
    Geometry::Solver solver_;
    std::thread solving_thread_;
    std::function<void(Geometry::VolumePuzzle&)> on_new_solution_callback_;
};
