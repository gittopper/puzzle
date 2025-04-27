#include <desktop/glrenderer.h>

#include <GL/gl.h>

GLRenderer::GLRenderer() {}

void GLRenderer::setup() {
    glFrontFace(GL_CCW);
    glEnable(GL_COLOR_MATERIAL);
    glClearColor(0.5, 0.5, 0.5, 1.0);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);

    GLfloat diffuse[] = {1.0, 1.0, 1.0, 1.0};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glEnable(GL_LIGHT0);

    GLfloat pos[] = {2.0, 3.0, 15.0, 0.0};
    glLightfv(GL_LIGHT0, GL_POSITION, pos);

    glShadeModel(GL_SMOOTH);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}

void GLRenderer::drawOverlay(const Sprite& sprite) {
    assert(sprite.type() == Sprite::RGBA);
    glEnable(GL_TEXTURE_2D);
    glActiveTexture(GL_TEXTURE0);
    GLuint overlay_id;
    glGenTextures(1, &overlay_id);
    glBindTexture(GL_TEXTURE_2D, overlay_id);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sprite.glWidth(), sprite.glHeight(),
                 0, GL_RGBA, GL_UNSIGNED_BYTE, sprite.data());

    glColor4f(1., 1., 1., 0.5);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    auto overlay_points = camera_.overlayPoints();

    GLfloat texCoords[] = {
        0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
    };
    GLuint indices3[] = {0, 1, 2, 3};
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_INDEX_ARRAY);

    glDisable(GL_LIGHTING);

    glVertexPointer(3, GL_FLOAT, 0, overlay_points.data());
    glTexCoordPointer(2, GL_FLOAT, 0, texCoords);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, indices3);

    glEnable(GL_LIGHTING);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_INDEX_ARRAY);
    glDeleteTextures(1, &overlay_id);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void GLRenderer::startFrame() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    const auto view = camera_.viewMatrix();
    glMultMatrixf(&view[0][0]);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    auto projection = camera_.projMatrix();
    glMultMatrixf(&projection[0][0]);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    drawLCS();

    glColor3f(0.2f, 0.0f, 0.0f);
}

void GLRenderer::finishFrame() {
    glPopMatrix();
    glFlush();
}

void GLRenderer::resize(int width, int height) {
    camera_.setViewport(width, height);
    glViewport(0, 0, width, height);
}

void GLRenderer::drawLCS() {
    glLineWidth(2.0);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(2., 0, 0);
    glEnd();

    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0., 2, 0);
    glEnd();

    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0., 0, 2);
    glEnd();
}
