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
    piecesset_renderer_(*renderer) {
    solving_thread_ = std::thread([this]() {
        solver_.solve();
    });

    auto daco2 = resource_loader->readFile("daco2.png");
    PngReader png_reader;
    sprite_ = png_reader.read(daco2, false);

    FT_Library library;

    if (FT_Init_FreeType(&library)) {
        throw std::runtime_error("FT_Init_FreeType failed");
    }
    auto font = resource_loader->readFile("XI20.ttf");
    FT_Face face;
    if (FT_New_Memory_Face(library, reinterpret_cast<FT_Byte*>(font.data()),
                           font.size(), 0, &face)) {
        throw std::runtime_error("FT_Init_FreeType failed");
    }
    int h = 50;
    FT_Set_Char_Size(face, h << 6, h << 6, 96, 96);
    FT_UInt glyph_index = FT_Get_Char_Index(face, U'Ж');
    if (FT_Load_Glyph(face, glyph_index, FT_LOAD_RENDER)) {
        throw std::runtime_error("FT_Load_Glyph failed");
    }
    FT_Bitmap* bitmap = &(face->glyph->bitmap);
    auto x = 10 + face->glyph->bitmap_left;
    auto y = 10 + face->glyph->bitmap_top;
    for (auto c = 0; c < bitmap->width; c++) {
        for (auto r = 0; r < bitmap->rows; r++) {
            auto gray = bitmap->buffer[r * bitmap->pitch + c];
            if (gray > 0) {
                sprite_.value().setPixel(x + c, y + r, gray, gray, gray, 255);
            }
        }
    }
    x += (face->glyph->advance.x >> 6);
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
