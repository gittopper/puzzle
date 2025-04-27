#include "volpartrenderer.h"

#include "math.h"
#include "piece.h"

using namespace Geometry;

void VolPartRenderer::drawSquare(const Geometry::Vector& shift,
                                 const Geometry::Vector& v1,
                                 const Geometry::Vector& v2,
                                 const Geometry::Vector& v3,
                                 const Geometry::Vector& v4,
                                 const Geometry::Vector& n) const {
    std::vector<Geometry::Vector> vertices;
    vertices.push_back(
        Geometry::Vector(shift[0] + v1[0], shift[1] + v1[1], shift[2] + v1[2]));
    vertices.push_back(
        Geometry::Vector(shift[0] + v2[0], shift[1] + v2[1], shift[2] + v2[2]));
    vertices.push_back(
        Geometry::Vector(shift[0] + v3[0], shift[1] + v3[1], shift[2] + v3[2]));
    vertices.push_back(
        Geometry::Vector(shift[0] + v4[0], shift[1] + v4[1], shift[2] + v4[2]));
    std::vector<Geometry::Vector> normals;
    normals.push_back(n);
    normals.push_back(n);
    normals.push_back(n);
    normals.push_back(n);
    std::vector<std::uint16_t> indices{0, 1, 2, 0, 2, 3};
    std::vector<Geometry::Vector> colors = {cur_color_, cur_color_, cur_color_,
                                            cur_color_};
    renderer_->render(reinterpret_cast<GLfloat*>(vertices.data()),
                      reinterpret_cast<GLfloat*>(normals.data()),
                      reinterpret_cast<GLfloat*>(colors.data()),
                      reinterpret_cast<GLushort*>(indices.data()), 6);
}

void VolPartRenderer::drawTriangle(const Geometry::Vector& shift,
                                   const Geometry::Vector& v1,
                                   const Geometry::Vector& v2,
                                   const Geometry::Vector& v3,
                                   const Geometry::Vector& n) const {
    std::vector<Geometry::Vector> vertices;
    vertices.push_back(
        Geometry::Vector(shift[0] + v1[0], shift[1] + v1[1], shift[2] + v1[2]));
    vertices.push_back(
        Geometry::Vector(shift[0] + v2[0], shift[1] + v2[1], shift[2] + v2[2]));
    vertices.push_back(
        Geometry::Vector(shift[0] + v3[0], shift[1] + v3[1], shift[2] + v3[2]));
    std::vector<Geometry::Vector> normals;
    normals.push_back(n);
    normals.push_back(n);
    normals.push_back(n);
    std::vector<std::uint16_t> indices{0, 1, 2};
    std::vector<Geometry::Vector> colors = {cur_color_, cur_color_, cur_color_};
    renderer_->render(reinterpret_cast<GLfloat*>(vertices.data()),
                      reinterpret_cast<GLfloat*>(normals.data()),
                      reinterpret_cast<GLfloat*>(colors.data()),
                      reinterpret_cast<GLushort*>(indices.data()), 3);
}

void VolPartRenderer::setColor(const Geometry::Vector& color) const {
    cur_color_ = color;
}
