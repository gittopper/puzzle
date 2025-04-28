#include <desktop/glutrenderer.h>

#include <tests.h>
#include <thread>

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
