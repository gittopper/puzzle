#pragma once

#include <piece.h>
#include <ivolpartrenderer.h>

class PiecesSetRenderer {
public:
    PiecesSetRenderer(IVolPartRendererPtr vol_part_renderer):
        vol_part_renderer_(std::move(vol_part_renderer)){}
    void render(const Geometry::PiecesSet& pieces_set);
    void render(const Geometry::Piece& piece, const Geometry::Vector& color);
private:
    Geometry::Vector getColor(std::size_t piece_id);
    std::vector<Geometry::Vector> colors_;
    IVolPartRendererPtr vol_part_renderer_;
};
