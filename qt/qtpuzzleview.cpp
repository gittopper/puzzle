#include <QDebug>

#include <desktop/glrenderer.h>

#include <qtpuzzleview.h>
#include <utils.h>

QTPuzzleView::QTPuzzleView(QWidget* parent) :
    QGLWidget(parent),
    puzzle_(3, 4, 2, generateWoodPuzzles()),
    //   puzzle_(2,2,2,generateTestPuzzles()),
    //   puzzle_(3,3,3,generateSomaPuzzles()),
    engine_(puzzle_, std::make_shared<GLRenderer>()) {
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    timer.start(16);
}

void QTPuzzleView::initializeGL() {
    engine_.setup();
}

void QTPuzzleView::paintGL() {
    engine_.display();
}

void QTPuzzleView::resizeGL(int w, int h) {
    engine_.resize(w, h);
}

void QTPuzzleView::mousePressEvent(QMouseEvent* me) {
    QPoint p = me->pos();
    switch (me->button()) {
        case Qt::LeftButton:
            engine_.rotateStart(p.x(), p.y());
            break;
        case Qt::RightButton:
            engine_.shiftStart(p.x(), p.y());
            break;
    }
}

void QTPuzzleView::mouseReleaseEvent(QMouseEvent* me) {
    QPoint p = me->pos();
    switch (me->button()) {
        case Qt::LeftButton:
            engine_.dragStop();
            break;
        case Qt::RightButton:
            engine_.dragStop();
            break;
    }
}
void QTPuzzleView::mouseMoveEvent(QMouseEvent* me) {
    QPoint p = me->pos();
    engine_.drag(p.x(), p.y());
}

void QTPuzzleView::wheelEvent(QWheelEvent* we) {
    QPoint p = we->pos();
    if (we->delta() > 0) {
        engine_.zoom(1.1);
    } else {
        engine_.zoom(0.9);
    }
    engine_.zoomDrag();
    engine_.dragStop();
}

void QTPuzzleView::renderSolution(int i) {
    engine_.showSolution(i);
}
