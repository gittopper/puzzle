#include "qtpuzzlerenderer.h"

#include <QDebug>

QTPuzzleRenderer::QTPuzzleRenderer(QWidget* parent) : QGLWidget(parent) {
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    timer.start(16);
}

void QTPuzzleRenderer::initializeGL() {
    initOpenGL();
}

void QTPuzzleRenderer::paintGL() {
    display();
}

void QTPuzzleRenderer::resizeGL(int w, int h) {
    GLRenderer::resize(w, h);
    //    qDebug() << "size: " << w << ", " << h;
}

void QTPuzzleRenderer::mousePressEvent(QMouseEvent* me) {
    QPoint p = me->pos();
    switch (me->button()) {
        case Qt::LeftButton:
            mouseLButtonDown(p.x(), p.y());
            break;
        case Qt::RightButton:
            mouseRButtonDown(p.x(), p.y());
            break;
    }
}

void QTPuzzleRenderer::mouseReleaseEvent(QMouseEvent* me) {
    QPoint p = me->pos();
    switch (me->button()) {
        case Qt::LeftButton:
            mouseLButtonUp(p.x(), p.y());
            break;
        case Qt::RightButton:
            mouseRButtonUp(p.x(), p.y());
            break;
    }
}
void QTPuzzleRenderer::mouseMoveEvent(QMouseEvent* me) {
    QPoint p = me->pos();
    mouseMove(p.x(), p.y());
}

void QTPuzzleRenderer::wheelEvent(QWheelEvent* we) {
    // setZoom(we->delta());
    QPoint p = we->pos();
    if (we->delta() > 0) {
        wheelUp(p.x(), p.y());
    } else {
        wheelDown(p.x(), p.y());
    }
}

void QTPuzzleRenderer::renderSolution(int i) {
    showSolution(i);
}
