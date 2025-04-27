#include "engine.h"

Engine::Engine(Geometry::VolumePuzzle& puzzle) :
    puzzle_(puzzle), solver_(puzzle) {
    solving_thread_ = std::thread([this]() {
        solver_.solve();
    });
    renderer_.setPuzzleToRender(puzzle_);
}

Engine::~Engine() {
    solver_.stopSolving();
    solving_thread_.join();
}

void Engine::setup() {
    renderer_.initOpenGL();
}

void Engine::display() {
    renderer_.display();
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
    renderer_.showSolution(i);
}
