#include <desktop/glutrenderer.h>

#include <sstream>

#include <GL/freeglut.h>

namespace {

GlutRenderer* glutRenderer;
}

class GlutBootstrap {
  public:
    static void render() {
        glutRenderer->display();
    }
    static void resize(int w, int h) {
        glutRenderer->resize(w, h);
    }

    static void mouseLButtonDown(int x, int y) {
        glutRenderer->mouseLButtonDown(x, y);
    }
    static void mouseLButtonUp(int x, int y) {
        glutRenderer->mouseLButtonUp(x, y);
    }

    static void mouseRButtonDown(int x, int y) {
        glutRenderer->mouseRButtonDown(x, y);
    }
    static void mouseRButtonUp(int x, int y) {
        glutRenderer->mouseRButtonUp(x, y);
    }

    static void wheelUp(int x, int y) {
        glutRenderer->wheelUp(x, y);
    }

    static void wheelDown(int x, int y) {
        glutRenderer->wheelDown(x, y);
    }

    //    static void rotateX(float x) {
    //        glutRenderer->rotateX(x);
    //    }

    //    static void rotateY(float y) {
    //        glutRenderer->rotateY(y);
    //    }

    static void mouseMove(int x, int y) {
        glutRenderer->mouseMove(x, y);
    }

    static void showSolution(int i) {
        glutRenderer->showSolution(i);
    }
};

void reshape(int w, int h) {
    GlutBootstrap::resize(w, h);
}

void glutDisplayImpl() {
    GlutBootstrap::render();
    glutSwapBuffers();
}

void refresh(int v) {
    glutPostRedisplay();
    glutTimerFunc(10, refresh, 0);
}

void specialKeys(int key, int x, int y) {
    //    //  Right arrow - increase rotation by 5 degree
    //    if (key == GLUT_KEY_RIGHT) GlutBootstrap::rotateY(5);

    //    //  Left arrow - decrease rotation by 5 degree
    //    else if (key == GLUT_KEY_LEFT)
    //        GlutBootstrap::rotateY(-5);

    //    else if (key == GLUT_KEY_UP)
    //        GlutBootstrap::rotateX(5);

    //    else if (key == GLUT_KEY_DOWN)
    //        GlutBootstrap::rotateX(-5);

    //  Request display update
    glutPostRedisplay();
}

void menu(int item) {
    GlutBootstrap::showSolution(item);
}

void GlutRenderer::addMenuEntry(int i) {
    std::stringstream s;
    s << i;
    glutAddMenuEntry(s.str().c_str(), i);
}

void mouse(int button, int state, int x, int y) {
    // Wheel reports as button 3(scroll up) and button 4(scroll down)
    if ((button == 3) || (button == 4))  // It's a wheel event
    {
        // Each wheel event reports like a button click, GLUT_DOWN then GLUT_UP
        if (state == GLUT_UP) return;  // Disregard redundant GLUT_UP events
        if (button == 3) GlutBootstrap::wheelUp(x, y);
        if (button == 4) GlutBootstrap::wheelDown(x, y);
    } else {  // normal button event

        if (state == GLUT_UP) {
            if (button == 0) GlutBootstrap::mouseLButtonUp(x, y);
            if (button == 2) GlutBootstrap::mouseRButtonUp(x, y);
        }
        if (state == GLUT_DOWN) {
            if (button == 0) GlutBootstrap::mouseLButtonDown(x, y);
            if (button == 2) GlutBootstrap::mouseRButtonDown(x, y);
        }
    }
}

void mousemove(int x, int y) {
    GlutBootstrap::mouseMove(x, y);
}

void GlutRenderer::init(int argc, char** argv) {
    glutInit(&argc, argv);

    resize(800, 800);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 200);
    glutCreateWindow("Puzzle visualizer");

    glutCreateMenu(menu);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    initOpenGL();

    glutRenderer = this;
    glutDisplayFunc(glutDisplayImpl);
    glutReshapeFunc(reshape);
    glutSpecialFunc(specialKeys);
    glutMouseFunc(mouse);
    glutMotionFunc(mousemove);

    glutTimerFunc(1, refresh, 0);
}

void GlutRenderer::run() {
    glutMainLoop();
}
