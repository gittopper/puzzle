#include <thread>

#include "geometry.h"
#include "glutrenderer.h"
#include "tests.h"

using namespace Geometry;

int main(int argc, char** argv) {
    BREAK_ON_LINE(makeGeneralTests());

    // solve55();

    GlutRenderer glutRenderer;

    glutRenderer.init(argc, argv);
    glutRenderer.run();

    std::cout << "Press any key to exit...";
    std::cin.get();

    return 0;
}
