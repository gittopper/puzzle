cmake_minimum_required (VERSION 3.18)

project (PuzzleSolver)

enable_language(CXX)

option(ANDROID_REGIME "android regime" OFF)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -fPIC -pthread")

set(COMMON_HEADERS
src/base.h
src/bbox.h
src/box.h
src/camera.h
src/geometry.h
src/mat.h
src/print.h
src/timer.h
src/logger.hpp
src/puzzle55.h
src/solver.h
src/utils.h
src/volpart.h
src/resourceloader.h
src/piecessetrenderer.h
src/idrawer.h
src/volumepuzzle.h
src/piece.h
src/ivolpartrenderer.h
src/utils3d.h
src/vector.h
)

set(COMMON_SOURCES
src/box.cpp
src/camera.cpp
src/mat.cpp
src/print.cpp
src/solver.cpp
src/utils.cpp
src/pngreader.cpp
src/volpart.cpp
src/volumepuzzle.cpp
src/piece.cpp
src/ivolpartrenderer.cpp
src/piecessetrenderer.cpp
src/utils3d.cpp
src/vector.cpp
)

add_subdirectory(src/3rd_party)

if (ANDROID_REGIME)

set(ANDROID_SOURCES
        src/android/Native.cpp
        src/android/renderer.cpp
        src/android/volpartrenderer.cpp
        )
set(TARGET Native)
add_library(${TARGET} SHARED ${COMMON_SOURCES} ${ANDROID_SOURCES})
target_include_directories(${TARGET} PUBLIC
    src
    src/android
)
target_link_libraries(${TARGET} PUBLIC log android EGL GLESv2 OpenSLES  dl  GLESv1_CM)
set_target_properties(${TARGET} PROPERTIES LIBRARY_OUTPUT_NAME ${TARGET})
find_package(OpenMP REQUIRED)

target_link_libraries(${TARGET} PUBLIC OpenMP::OpenMP_CXX glm::glm-header-only
     png_static zlibstatic
     )

else()

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(QT_SOURCES
src/desktop/glrenderer.h
#src/desktop/glutrenderer.h
src/desktop/volpartrenderer.h
src/desktop/fileresourceloader.h
src/desktop/glrenderer.cpp
#src/desktop/glutrenderer.cpp
src/desktop/volpartrenderer.cpp
src/desktop/fileresourceloader.cpp
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

add_executable(qtSolver ${COMMON_HEADERS} ${COMMON_SOURCES} ${QT_SOURCES})

target_include_directories(qtSolver PUBLIC
src
src/desktop
qt
)
file(COPY src/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

target_compile_definitions(qtSolver PUBLIC
    GLM_ENABLE_EXPERIMENTAL=ON)

find_package(OpenMP REQUIRED)

target_link_libraries(qtSolver GL glut GLU Qt5::Widgets Qt5::Gui
    Qt5::OpenGL OpenMP::OpenMP_CXX glm::glm-header-only
     png_static zlibstatic
     )

endif()
