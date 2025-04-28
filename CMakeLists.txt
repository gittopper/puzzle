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
src/engine.h
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
src/volumepuzzle.h
src/piece.h
src/irenderer.h
src/vector.h
)

set(COMMON_SOURCES
src/box.cpp
src/camera.cpp
src/mat.cpp
src/print.cpp
src/solver.cpp
src/engine.cpp
src/utils.cpp
src/pngreader.cpp
src/volpart.cpp
src/volumepuzzle.cpp
src/piece.cpp
src/irenderer.cpp
src/piecessetrenderer.cpp
src/vector.cpp
src/tests.cpp
)

add_subdirectory(src/3rd_party)

if (ANDROID_REGIME)

set(ANDROID_SOURCES
        src/android/native.cpp
        src/android/glesrenderer.cpp
        src/android/androidresourceloader.cpp
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

set(DESKTOP_SOURCES
src/desktop/glrenderer.h
src/desktop/fileresourceloader.h
src/desktop/glrenderer.cpp
src/desktop/fileresourceloader.cpp
)
set(QT_SOURCES
qt/qtvolumepuzzle.h
qt/qtpuzzleview.h
qt/qtsolutionslist.h
qt/mainwindow.h
qt/mainwindow.ui
qt/mainwindow.cpp
qt/qt_main.cpp
qt/qtvolumepuzzle.cpp
qt/qtpuzzleview.cpp
qt/qtsolutionslist.cpp
)

add_executable(qt_solver ${COMMON_HEADERS} ${COMMON_SOURCES} ${DESKTOP_SOURCES} ${QT_SOURCES})

target_include_directories(qt_solver PUBLIC
src
src/desktop
qt
)
target_compile_definitions(qt_solver PUBLIC QT_ENV=ON)
file(COPY src/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

find_package(OpenMP REQUIRED)

target_link_libraries(qt_solver GL GLU Qt5::Widgets Qt5::Gui
    Qt5::OpenGL OpenMP::OpenMP_CXX glm::glm-header-only
     png_static zlibstatic
     )


add_executable(glut_solver
     ${COMMON_HEADERS}
     ${COMMON_SOURCES}
     ${DESKTOP_SOURCES}
     src/desktop/main.cpp
     src/desktop/glutrenderer.cpp
)

 target_include_directories(glut_solver PUBLIC
 src
 )

 find_package(OpenMP REQUIRED)

 target_link_libraries(glut_solver GL glut GLU
     OpenMP::OpenMP_CXX
     glm::glm-header-only
     png_static zlibstatic
)

endif()
