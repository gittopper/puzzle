#include <thread>

#include "geometry.h"
#include "glutrenderer.h"
#include "tests.h"

using namespace Geometry;

int main(int argc, char** argv) {
    BREAK_ON_LINE(makeGeneralTests());

    // solve55();

    VolumePuzzle puzzle(3, 4, 2, generateWoodPuzzles());
    //   Solver VolumePuzzle(2,2,2,generateTestPuzzles());
    //   Solver VolumePuzzle(3,3,3,generateSomaPuzzles());

    std::thread st([&puzzle]() {
        Solver solver(puzzle);
        solver.solve();
    });

    GlutRenderer glutRenderer;

    glutRenderer.init(argc, argv);
    glutRenderer.setPuzzleToRender(puzzle);
    glutRenderer.run();

    st.join();

    std::cout << "Press any key to exit...";
    std::cin.get();

    return 0;
}
