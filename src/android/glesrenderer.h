#pragma once

#include <irenderer.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

class GLESRenderer : public IRenderer {
  public:
    void setup() override;
    void resize(int width, int height) override;
    void startFrame() override;
    void finishFrame() override;
    Camera& camera() {
        return camera_;
    }
    void drawOverlay(const Sprite& sprite) override;

    void drawSquare(const Geometry::Vector& shift,
                    const Geometry::Vector& v1,
                    const Geometry::Vector& v2,
                    const Geometry::Vector& v3,
                    const Geometry::Vector& v4,
                    const Geometry::Vector& n) const override;

    void drawTriangle(const Geometry::Vector& shift,
                      const Geometry::Vector& v1,
                      const Geometry::Vector& v2,
                      const Geometry::Vector& v3,
                      const Geometry::Vector& n) const override;
    void setColor(const Geometry::Vector& color) const override;

  private:
    void render(GLfloat* vertices,
                GLfloat* normals,
                GLfloat* colors,
                GLushort* indices,
                int size) const;
    GLuint loadShader(GLenum shaderType, const char* shaderSource);
    GLuint createProgram(const char* vertexSource, const char* fragmentSource);

    GLuint volume_part_program_;
    GLuint vertex_location_;
    GLuint vertex_color_location_;
    GLuint projection_location_;
    GLuint vertex_normal_location_;
    GLuint model_view_location_;

    GLuint overlay_program_;
    GLuint overlay_vert_loc_;
    GLuint overlay_tex_loc_;
    GLuint overlay_mat_loc_;
    mutable Geometry::Vector cur_color_;
};
