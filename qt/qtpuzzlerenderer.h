#ifndef QTPUZZLERENDERER_H
#define QTPUZZLERENDERER_H

#include <QGLWidget>
#include <QTimer>
#include "glrenderer.h"
#include <QWheelEvent>

class QTPuzzleRenderer : public QGLWidget, public GLRenderer
{
    Q_OBJECT
public:
    explicit QTPuzzleRenderer(QWidget *parent = 0);

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
    void wheelEvent(QWheelEvent* we);
    void mousePressEvent(QMouseEvent* me);
    void mouseMoveEvent(QMouseEvent* me);
public slots:
    void renderSolution(int i);
private:
    QTimer timer;
};

#endif // QTPUZZLERENDERER_H
