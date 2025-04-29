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
    font_(std::make_shared<Font>(resource_loader->readFile("XI20.ttf"))),
    menu_(font_) {
    solving_thread_ = std::thread([this]() {
        solver_.solve();
    });

    auto daco2 = resource_loader->readFile("daco2.png");
    PngReader png_reader;
    sprite_ = png_reader.read(daco2, false);
}

Engine::~Engine() {
    solver_.stopSolving();
    solving_thread_.join();
}

void Engine::setup() {
    renderer_->setup();
}

void Engine::renderOverlay() {
    if (menu_.items().size() != puzzle_.numFoundSolutions() ||
        sprite_.value().width() != renderer_->camera().width() ||
        sprite_.value().height() != renderer_->camera().height()) {
        sprite_ = Sprite(renderer_->camera().width(),
                         renderer_->camera().height(), Sprite::RGBA);
        Geometry::PiecesSet sol;
        std::vector<UString> items;
        for (auto i = 1UL; i <= puzzle_.numFoundSolutions(); ++i) {
            puzzle_.getSolution(sol, i);
            std::stringstream s;
            s << i << "(" << sol.tag() << ")";
            items.push_back(Font::convertToUtf32(s.str()));
        }
        menu_.setItems(items);
        menu_.render(sprite_.value());
    }
}

void Engine::display() {
    renderer_->startFrame();
    Geometry::PiecesSet sol;
    int ns = puzzle_.numFoundSolutions();
    int i = cur_sol_ > 0 ? cur_sol_ : ns;
    puzzle_.getSolution(sol, i);

    piecesset_renderer_.render(sol);

    renderOverlay();
    if (sprite_.has_value()) {
        renderer_->drawOverlay(sprite_.value());
    }

    renderer_->finishFrame();
}

void Engine::resize(int width, int height) {
    renderer_->resize(width, height);
    renderOverlay();
}

void Engine::rotateStart(int x, int y) {
    renderer_->camera().rotateStart(x, y);
    auto selected_item = menu_.selectItem(x, y);
    if (selected_item >= 0) {
        showSolution(selected_item + 1);
    }
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
