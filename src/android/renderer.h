#pragma once

#include <android/log.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#define LOG_TAG "libNative"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

#include <camera.h>
#include <memory>
#include <optional>
#include <sprite.h>

class Renderer {
  public:
    void setup();
    void setSize(int width, int height);
    void startFrame();
    void finishFrame();
    Camera& camera() {
        return camera_;
    }
    void render(GLfloat* vertices,
                GLfloat* normals,
                GLfloat* colors,
                GLushort* indices,
                int size);
    void setSprite(const std::optional<Sprite>& sprite) {
        sprite_ = sprite;
    }

  private:
    GLuint loadShader(GLenum shaderType, const char* shaderSource);
    GLuint createProgram(const char* vertexSource, const char* fragmentSource);
    void drawOverlay(const Sprite& sprite);

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

    Camera camera_;
    std::optional<Sprite> sprite_;
};

using RendererPtr = std::shared_ptr<Renderer>;
