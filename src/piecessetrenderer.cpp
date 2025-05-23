#include <piecessetrenderer.h>

PiecesSetRenderer::PiecesSetRenderer(IRenderer& vol_part_renderer) :
    vol_part_renderer_(vol_part_renderer),
    engine_(fixed_colors_ ? 777 : std::random_device()()),
    dist_(0, 1) {}

void PiecesSetRenderer::render(const Geometry::PiecesSet& pieces_set) {
    Geometry::Vector cm;
    for (const auto& piece : pieces_set) {
        cm += piece.getZero();
    }
    cm = cm * (1.f / pieces_set.size());
    for (auto& piece : pieces_set) {
        auto temp = piece;
        temp.shift(-cm + (piece.getZero() - cm) * 0.2f);
        render(temp, getColor(piece.id));
    }
}
void PiecesSetRenderer::render(const Geometry::Piece& piece,
                               const Geometry::Vector& color) {
    for (auto& part : piece.parts) {
        vol_part_renderer_.render(part, color);
    }
}

Geometry::Vector PiecesSetRenderer::getColor(std::size_t piece_id) {
    while (colors_.size() <= piece_id) {
        colors_.push_back(
            Geometry::Vector(dist_(engine_), dist_(engine_), dist_(engine_)));
    }
    assert(piece_id < colors_.size());
    return colors_[piece_id];
}
