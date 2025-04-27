#include "engine.h"

#include <desktop/volpartrenderer.h>

Engine::Engine(Geometry::VolumePuzzle& puzzle) :
    puzzle_(puzzle),
    solver_(puzzle),
    piecesset_renderer_(std::make_shared<VolPartRenderer>()) {
    solving_thread_ = std::thread([this]() {
        solver_.solve();
    });
}

Engine::~Engine() {
    solver_.stopSolving();
    solving_thread_.join();
}

void Engine::setup() {
    renderer_.setup();
}

void Engine::display() {
    renderer_.startFrame();
    Geometry::PiecesSet sol;
    int ns = puzzle_.numFoundSolutions();
    int i = cur_sol_ > 0 ? cur_sol_ : ns;
    puzzle_.getSolution(sol, i);

    piecesset_renderer_.render(sol);

    renderer_.finishFrame();
}

void Engine::resize(int width, int height) {
    renderer_.resize(width, height);
}

void Engine::rotateStart(int x, int y) {
    renderer_.camera().rotateStart(x, y);
}

void Engine::shiftStart(int x, int y) {
    renderer_.camera().shiftStart(x, y);
}

void Engine::drag(int x, int y) {
    renderer_.camera().drag(x, y);
}

void Engine::dragStop() {
    renderer_.camera().store();
}

void Engine::zoom(float z) {
    renderer_.camera().zoom(z);
}

void Engine::zoomDrag() {
    renderer_.camera().zoomDrag();
}

void Engine::showSolution(std::size_t i) {
    cur_sol_ = i;
}
