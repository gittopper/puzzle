cmake_minimum_required (VERSION 2.8.7)

project (PuzzleSolver)

enable_language(CXX)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fPIC -pthread")

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)

include_directories(
include
3rdParty/glm/
src
qt
${Qt5Widgets_INCLUDE_DIRS}
${Qt5Gui_INCLUDE_DIRS}
${Qt5Widgets_INCLUDE_DIRS}
${Qt5OpenGL_INCLUDE_DIRS}
)


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(COMMON_HEADERS
include/base.h
include/camera.h
include/bbox.h
include/box.h
include/geometry.h
include/mat.h
include/print.h
include/timer.h
include/logger.hpp
include/puzzle55.h
include/solver.h
include/utils.h
include/volpart.h

include/idrawer.h
include/tests.h
include/volumepuzzle.h
include/glrenderer.h
include/camera.h
include/object3d.h
include/piece.h
include/pieceshower.h
include/utils3d.h
include/vector.h
)

set(COMMON_SOURCES
src/camera.cpp
src/box.cpp
src/mat.cpp
src/print.cpp
src/solver.cpp
src/utils.cpp
src/volpart.cpp
src/tests.cpp
src/volumepuzzle.cpp
src/glrenderer.cpp
src/camera.cpp
src/object3d.cpp
src/piece.cpp
src/pieceshower.cpp
src/utils3d.cpp
src/vector.cpp

)

set(QT_SOURCES
qt/qtvolumepuzzle.h
qt/qtpuzzlerenderer.h
qt/qtsolutionslist.h
qt/mainwindow.h
qt/mainwindow.ui
qt/mainwindow.cpp
qt/qt_main.cpp
qt/qtvolumepuzzle.cpp
qt/qtpuzzlerenderer.cpp
qt/qtsolutionslist.cpp
)

set(GLUT_LIBS GL glut GLU)

add_executable(qtSolver ${COMMON_HEADERS} ${COMMON_SOURCES} ${QT_SOURCES})

qt5_use_modules(qtSolver Core Gui Widgets OpenGL)
find_package(OpenMP REQUIRED)

target_link_libraries(qtSolver ${GLUT_LIBS} ${QT_LIBRARIES} OpenMP::OpenMP_CXX)
