#ifndef QTPUZZLERENDERER_H
#define QTPUZZLERENDERER_H

#include <QGLWidget>
#include <QTimer>
#include <QWheelEvent>

#include "glrenderer.h"

class QTPuzzleRenderer : public QGLWidget, public Geometry::GLRenderer {
    Q_OBJECT
  public:
    explicit QTPuzzleRenderer(QWidget* parent = 0);

    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;
    void wheelEvent(QWheelEvent* we) override;
    void mousePressEvent(QMouseEvent* me) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* me) override;
  public slots:
    void renderSolution(int i);

  private:
    QTimer timer;
};

#endif  // QTPUZZLERENDERER_H
