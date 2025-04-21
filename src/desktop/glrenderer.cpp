#include "volpartrenderer.h"
#include <glrenderer.h>
#include <print.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <cstdlib>
#include <time.h>
#include <desktop/fileresourceloader.h>
#include <QApplication>
#include <pngreader.h>

namespace Geometry
{

GLRenderer::GLRenderer():
renderer_(std::make_shared<VolPartRenderer>())
{}

void GLRenderer::initOpenGL()
{
    glFrontFace(GL_CCW);
    //glMatrixMode(GL_PROJECTION);
    glEnable(GL_COLOR_MATERIAL);
    glClearColor(0.5, 0.5, 0.5, 1.0);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);

    GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glEnable(GL_LIGHT0);


    GLfloat pos[] = { 2.0, 3.0, 15.0, 0.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, pos);

    glShadeModel(GL_SMOOTH);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    cur_sol_ = 0;
    max_sol_ = 0;

    FileResourceLoader frl;
    auto path = QApplication::applicationDirPath().toStdString() + "/assets/daco2.png";
    auto daco2 = frl.readFile(path);
    PngReader png_reader;
    sprite_ = png_reader.read(daco2, false);
}

void GLRenderer::showSolution(int sol)
{
    cur_sol_ = sol;
}

void GLRenderer::drawOverlay(const Sprite& sprite) {
    assert(sprite.type() == Sprite::RGBA);
    glEnable(GL_TEXTURE_2D);
    glActiveTexture(GL_TEXTURE0);
    GLuint overlay_id;
    glGenTextures(1, &overlay_id);
    glBindTexture(GL_TEXTURE_2D, overlay_id);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sprite.glWidth(), sprite.glHeight(), 0,
            GL_RGBA, GL_UNSIGNED_BYTE, sprite.data());

    glColor4f(1., 1., 1., 0.5);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    //glGenerateMipmap(GL_TEXTURE_2D);
    auto overlay_points = camera.overlayPoints();

    GLfloat texCoords[] = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
    };
    GLuint indices3[] = {
        0, 1, 2, 3
    };
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_INDEX_ARRAY);

//    glEnable(GL_COLOR_MATERIAL);
//    const GLfloat emi[4] = {1.0f, 1.0f, 1.0f, 0.5f};
//    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emi);

    glDisable(GL_LIGHTING);
    //glDisable(GL_LIGHT0);

    glVertexPointer  (3, GL_FLOAT, 0, overlay_points.data());
    glTexCoordPointer(2, GL_FLOAT, 0, texCoords);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, indices3);

    glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT0);
    //glDisable(GL_COLOR_MATERIAL);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_INDEX_ARRAY);
    glDeleteTextures(1, &overlay_id);
    glBindTexture(GL_TEXTURE_2D, 0);
    //glDisable(GL_TEXTURE_2D);
}

void GLRenderer::display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    camera.render();

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    drawLCS();

    glColor3f(0.2f, 0.0f, 0.0f);

    PiecesSet sol;
    int ns = puzzle_->numFoundSolutions();
    int i = cur_sol_ > 0 ? cur_sol_ : ns;
    puzzle_->getSolution(sol, i);

    if (ns > max_sol_)
    {
        for (int is = max_sol_ + 1; is <= ns; is++)
        {
            addMenuEntry(is);
        }
        max_sol_ = ns;
    }

    renderer_.render(sol);


    drawOverlay(sprite_.value());

    glPopMatrix();
    glFlush();
}

void GLRenderer::resize(int width, int height)
{
    camera.setViewport(width, height);
}


void GLRenderer::drawLCS()
{
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

void GLRenderer::setPuzzleToRender(VolumePuzzle& puzzleToRender)
{
    puzzle_ = &puzzleToRender;
}

void GLRenderer::mouseLButtonDown(int x, int y)
{
    lastX = x;
    lastY = y;
}

void GLRenderer::mouseLButtonUp(int x, int y)
{

}

void GLRenderer::mouseRButtonDown(int x, int y)
{
    lastX = x;
    lastY = y;
}

void GLRenderer::mouseMove(int x, int y)
{
    float speed = 0.01f;
    float angleX = (x - lastX) * speed;
    float angleY = -(y - lastY) * speed;
    lastX = x;
    lastY = y;

    camera.rotate(angleX, angleY);
}

void GLRenderer::mouseRButtonUp(int x, int y)
{

}

void GLRenderer::wheelUp(int x, int y)
{
    camera.zoom(1.1);
}

void GLRenderer::wheelDown(int x, int y)
{
    camera.zoom(0.9);
}
}
