#include "renderer.h"

static const char glVertexShader[] = R"(
attribute vec4 vertexPosition;
attribute vec3 vertexColour;
/* [Add a vertex normal attribute.] */
attribute vec3 vertexNormal;
/* [Add a vertex normal attribute.] */
varying vec3 fragColour;
uniform mat4 projection;
uniform mat4 modelView;
void main()
{
/* [Setup scene vectors.] */
    vec3 transformedVertexNormal = normalize((modelView * vec4(vertexNormal, 0.0)).xyz);
    vec3 inverseLightDirection = normalize(vec3(0.0, 1.0, 1.0));
    fragColour = vec3(0.0);
/* [Setup scene vectors.] */

/* [Calculate the diffuse component.] */
    vec3 diffuseLightIntensity = vec3(1.0, 1.0, 1.0);
    vec3 vertexDiffuseReflectionConstant = vertexColour;
    float normalDotLight = max(0.0, dot(transformedVertexNormal, inverseLightDirection));
    fragColour += normalDotLight * vertexDiffuseReflectionConstant * diffuseLightIntensity;
/* [Calculate the diffuse component.] */

/* [Calculate the ambient component.] */
    vec3 ambientLightIntensity = vec3(0.1, 0.1, 0.1);
    vec3 vertexAmbientReflectionConstant = vertexColour;
    fragColour += vertexAmbientReflectionConstant * ambientLightIntensity;
/* [Calculate the ambient component.] */

/* [Calculate the specular component.] */
    vec3 inverseEyeDirection = normalize(vec3(0.0, 0.0, 1.0));
    vec3 specularLightIntensity = vec3(1.0, 1.0, 1.0);
    vec3 vertexSpecularReflectionConstant = vec3(1.0, 1.0, 1.0);
    float shininess = 2.0;
    vec3 lightReflectionDirection = reflect(vec3(0) - inverseLightDirection, transformedVertexNormal);
    float normalDotReflection = max(0.0, dot(inverseEyeDirection, lightReflectionDirection));
    //fragColour += pow(normalDotReflection, shininess) * vertexSpecularReflectionConstant * specularLightIntensity;
/* [Calculate the specular component.] */

    /* Make sure the fragment colour is between 0 and 1. */
    clamp(fragColour, 0.0, 1.0);

    gl_Position = projection * modelView * vertexPosition;
}
)";
/* [vertexShader] */

/* [vertexShader] */
/*
static const char  glVertexShader[] = R"(
    attribute vec4 vertexPosition;
    attribute vec3 vertexColour;
    varying vec3 fragColour;
    uniform mat4 projection;
    uniform mat4 modelView;
    void main()
    {
        gl_Position = projection * modelView * vertexPosition;
        fragColour = vertexColour;
    }
)";
*/
/* [vertexShader] */

/* [fragmentShader] */
static const char glFragmentShader[] = R"(
    precision mediump float;
    varying vec3 fragColour;
    void main()
    {
        gl_FragColor = vec4(fragColour, 1.0);
    }
)";
/* [fragmentShader] */

const char* overlay_vertex_shader = R"(
attribute vec2 a_Texture;
attribute vec3 a_Position;
varying vec2 v_Texture;
uniform mat4 u_mvpMatrix;

void main()
{
    gl_Position = u_mvpMatrix * vec4(a_Position, 1.);
    v_Texture = a_Texture;
}
)";

const char* overlay_fragment_shader = R"(
precision mediump float;

uniform sampler2D u_TextureUnit;
varying vec2 v_Texture;

void main()
{
    gl_FragColor = texture2D(u_TextureUnit, v_Texture);
    gl_FragColor.a = 0.5;
    if (gl_FragColor.a < 0.1) {
        discard;
    }
}
)";

GLuint Renderer::loadShader(GLenum shaderType, const char* shaderSource) {
    GLuint shader = glCreateShader(shaderType);
    if (shader != 0) {
        glShaderSource(shader, 1, &shaderSource, NULL);
        glCompileShader(shader);
        GLint compiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (compiled != GL_TRUE) {
            GLint infoLen = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

            if (infoLen > 0) {
                char* logBuffer = (char*)malloc(infoLen);

                if (logBuffer != NULL) {
                    glGetShaderInfoLog(shader, infoLen, NULL, logBuffer);
                    LOGE("Could not Compile Shader %d:\n%s\n", shaderType,
                         logBuffer);
                    free(logBuffer);
                    logBuffer = NULL;
                }

                glDeleteShader(shader);
                shader = 0;
            }
        }
    }

    return shader;
}

GLuint Renderer::createProgram(const char* vertexSource,
                               const char* fragmentSource) {
    GLuint vertexShader = loadShader(GL_VERTEX_SHADER, vertexSource);
    if (vertexShader == 0) {
        return 0;
    }

    GLuint fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentSource);
    if (fragmentShader == 0) {
        return 0;
    }

    GLuint program = glCreateProgram();

    if (program != 0) {
        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);
        glLinkProgram(program);
        GLint linkStatus = GL_FALSE;
        glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
        if (linkStatus != GL_TRUE) {
            GLint bufLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
            if (bufLength > 0) {
                char* logBuffer = (char*)malloc(bufLength);

                if (logBuffer != NULL) {
                    glGetProgramInfoLog(program, bufLength, NULL, logBuffer);
                    LOGE("Could not link program:\n%s\n", logBuffer);
                    free(logBuffer);
                    logBuffer = NULL;
                }
            }
            glDeleteProgram(program);
            program = 0;
        }
    }
    return program;
}

void Renderer::setup() {
    volume_part_program_ = createProgram(glVertexShader, glFragmentShader);

    if (volume_part_program_ == 0) {
        LOGE("Could not create program");
    }
    glUseProgram(volume_part_program_);

    vertex_location_ =
        glGetAttribLocation(volume_part_program_, "vertexPosition");
    vertex_color_location_ =
        glGetAttribLocation(volume_part_program_, "vertexColour");
    projection_location_ =
        glGetUniformLocation(volume_part_program_, "projection");
    vertex_normal_location_ =
        glGetAttribLocation(volume_part_program_, "vertexNormal");
    model_view_location_ =
        glGetUniformLocation(volume_part_program_, "modelView");

    overlay_program_ =
        createProgram(overlay_vertex_shader, overlay_fragment_shader);

    if (overlay_program_ == 0) {
        LOGE("Could not create program");
    }
    glUseProgram(overlay_program_);

    overlay_vert_loc_ = glGetAttribLocation(overlay_program_, "a_Position");
    overlay_tex_loc_ =
        glGetAttribLocation(overlay_program_, "a_Texture");  // texture
    overlay_mat_loc_ =
        glGetUniformLocation(overlay_program_, "u_mvpMatrix");  // texture
}

void Renderer::resize(int width, int height) {
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, width, height);

    camera_.setViewport(width, height);
}
void Renderer::startFrame() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glUseProgram(volume_part_program_);
}

void Renderer::finishFrame() {
    if (sprite_.has_value()) {
        drawOverlay(sprite_.value());
    }
}

void Renderer::drawOverlay(const Sprite& sprite) {
    GLuint texture_id;
    glGenTextures(1, &texture_id);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sprite.glWidth(), sprite.glHeight(),
                 0, GL_RGBA, GL_UNSIGNED_BYTE, sprite.data());

    auto overlay_points = camera_.overlayPoints();

    GLfloat texture[] = {
        0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
    };

    glUseProgram(overlay_program_);
    glVertexAttribPointer(overlay_vert_loc_, 3, GL_FLOAT, false, 0,
                          &overlay_points[0]);
    glEnableVertexAttribArray(overlay_vert_loc_);

    glVertexAttribPointer(overlay_tex_loc_, 2, GL_FLOAT, false, 0, texture);
    glEnableVertexAttribArray(overlay_tex_loc_);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    auto mvp = camera_.mvp();
    glUniformMatrix4fv(overlay_mat_loc_, 1, GL_FALSE, (GLfloat*)&mvp[0][0]);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glDisable(GL_BLEND);

    glBindTexture(GL_TEXTURE_2D, 0);
    glDeleteTextures(1, &texture_id);
}

void Renderer::render(GLfloat* vertices,
                      GLfloat* normals,
                      GLfloat* colors,
                      GLushort* indices,
                      int size) {
    glVertexAttribPointer(vertex_location_, 3, GL_FLOAT, GL_FALSE, 0, vertices);
    glEnableVertexAttribArray(vertex_location_);
    glVertexAttribPointer(vertex_color_location_, 3, GL_FLOAT, GL_FALSE, 0,
                          colors);
    glEnableVertexAttribArray(vertex_color_location_);
    glVertexAttribPointer(vertex_normal_location_, 3, GL_FLOAT, GL_FALSE, 0,
                          normals);
    glEnableVertexAttribArray(vertex_normal_location_);
    glUniformMatrix4fv(projection_location_, 1, GL_FALSE,
                       &(camera_.projMatrix())[0][0]);
    glUniformMatrix4fv(model_view_location_, 1, GL_FALSE,
                       &(camera_.viewMatrix())[0][0]);

    glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_SHORT, indices);
}
