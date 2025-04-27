#pragma once

#include <QGLWidget>
#include <QTimer>
#include <QWheelEvent>

#include <engine.h>
#include <qtvolumepuzzle.h>

class QTPuzzleView : public QGLWidget {
    Q_OBJECT
  public:
    explicit QTPuzzleView(QWidget* parent = 0);

    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;
    void wheelEvent(QWheelEvent* we) override;
    void mousePressEvent(QMouseEvent* me) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* me) override;

    QTVolumePuzzle& puzzle() {
        return puzzle_;
    }
  public slots:
    void renderSolution(int i);

  private:
    QTVolumePuzzle puzzle_;
    Engine engine_;
    QTimer timer;
};
