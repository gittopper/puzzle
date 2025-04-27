#-------------------------------------------------
#
# Project created by QtCreator 2014-10-09T00:35:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets opengl

TARGET = qt_puzzle
TEMPLATE = app

INCLUDEPATH += ../include \

#    ../glutdlls37beta

SOURCES +=\
        mainwindow.cpp \
    ../src/box.cpp \
    ../src/mat.cpp \
    ../src/mutex.cpp \
    ../src/print.cpp \
    ../src/solver.cpp \
    ../src/threads.cpp \
    ../src/utils.cpp \
    ../src/volpart.cpp \
    qt_main.cpp \
    ../src/tests.cpp \
    ../src/volumepuzzle.cpp \
    ../src/glrenderer.cpp \
    qtvolumepuzzle.cpp \
    qtpuzzleview.cpp \
    ../src/camera.cpp \
    ../src/object3d.cpp \
    ../src/piece.cpp \
    ../src/pieceshower.cpp \
    ../src/utils3d.cpp \
    ../src/vector.cpp \
    qtsolutionslist.cpp

HEADERS  += mainwindow.h \
    ../include/base.h \
    ../include/bbox.h \
    ../include/box.h \
    ../include/geometry.h \
    ../include/mat.h \
    ../include/mutex.h \
    ../include/print.h \
    ../include/puzzle55.h \
    ../include/solver.h \
    ../include/threads.h \
    ../include/utils.h \
    ../include/volpart.h \
    ../include/idrawer.h \
    ../include/tests.h \
    ../include/volumepuzzle.h \
    ../include/glrenderer.h \
    qtvolumepuzzle.h \
    qtpuzzleview.h \
    ../include/camera.h \
    ../include/object3d.h \
    ../include/piece.h \
    ../include/pieceshower.h \
    ../include/utils3d.h \
    ../include/vector.h \
    qtsolutionslist.h

FORMS    += mainwindow.ui

#win32: LIBS += -L$$PWD/../glutdlls37beta/ -lglut32

#INCLUDEPATH += $$PWD/../glutdlls37beta
#DEPENDPATH += $$PWD/../glutdlls37beta

#win32: PRE_TARGETDEPS += $$PWD/../glutdlls37beta/glut32.lib
