#include "engine.h"

#include <desktop/fileresourceloader.h>
#include <freetype/freetype.h>

#include <pngreader.h>

Engine::Engine(Geometry::VolumePuzzle& puzzle,
               IRendererPtr renderer,
               ResourceLoaderPtr resource_loader) :
    puzzle_(puzzle),
    renderer_(renderer),
    solver_(puzzle),
    piecesset_renderer_(*renderer),
    font_(resource_loader->readFile("XI20.ttf")) {
    solving_thread_ = std::thread([this]() {
        solver_.solve();
    });

    auto daco2 = resource_loader->readFile("daco2.png");
    PngReader png_reader;
    sprite_ = png_reader.read(daco2, false);

    font_.setColor({255, 0, 255, 100});
    font_.setFontSize(100);
    auto text = U"Привет!:)";
    auto [text_width, text_height] = font_.getTextWidthHeight(text);
    sprite_.value().drawRect(10, 10, text_width, text_height, {0, 255, 0, 100});
    font_.renderText(sprite_.value(), 10, 10, text);
}

Engine::~Engine() {
    solver_.stopSolving();
    solving_thread_.join();
}

void Engine::setup() {
    renderer_->setup();
}

void Engine::display() {
    renderer_->startFrame();
    Geometry::PiecesSet sol;
    int ns = puzzle_.numFoundSolutions();
    int i = cur_sol_ > 0 ? cur_sol_ : ns;
    puzzle_.getSolution(sol, i);

    piecesset_renderer_.render(sol);

    if (sprite_.has_value()) {
        renderer_->drawOverlay(sprite_.value());
    }

    renderer_->finishFrame();
}

void Engine::resize(int width, int height) {
    renderer_->resize(width, height);
}

void Engine::rotateStart(int x, int y) {
    renderer_->camera().rotateStart(x, y);
}

void Engine::shiftStart(int x, int y) {
    renderer_->camera().shiftStart(x, y);
}

void Engine::drag(int x, int y) {
    renderer_->camera().drag(x, y);
}

void Engine::dragStop() {
    renderer_->camera().store();
}

void Engine::zoom(float z) {
    renderer_->camera().zoom(z);
}

void Engine::zoomDrag() {
    renderer_->camera().zoomDrag();
}

void Engine::showSolution(std::size_t i) {
    cur_sol_ = i;
}
