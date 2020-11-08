#include "game.h"

#include <chrono>

int main() {

    Game game("Learnin' Opengl",
              480, 480,
              4, 4,
              true);

    for (int i = 0; i < 20; i++)
        game.initialRender();

    auto start = std::chrono::high_resolution_clock::now();
    std::cout << "Calculating Depth map..." << std::endl;

    game.saveDepthMap();

    std::cout << "\t\t\t\t...Done" << std::endl;

    game.swapTorusAndBezier();

    Pixel *p;

    p = game.calculateNearestPixel();
    std::cout << "Torus touched at " << p->x_cord << ", " << p->y_cord << std::endl;
    std::cout << "Z movement required for first point of contact :  " << p->depth << std::endl;

    float zoomTolerance = 0.1;

    game.setOrthoMatrixBounds(p->x_cord-zoomTolerance, p->x_cord+zoomTolerance, p->y_cord-zoomTolerance, p->y_cord+zoomTolerance);
    game.swapTorusAndBezier();

    game.recalculateDepthMap();
    game.swapTorusAndBezier();

    game.setNewScaleFactor(zoomTolerance);

    Pixel *newP = game.reCalculateNearestPixel();

    std::cout << "[NEW] Torus touched at " << newP->x_cord << ", " << newP->y_cord << std::endl;
    std::cout << "[NEW] Z movement required for first point of contact :  " << newP->depth << std::endl;

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time taken by function: "
              << duration.count() << " microseconds" << std::endl;
    //MAIN LOOP
    while (!game.getWindowShouldClose()) {

        //UPDATE INPUT ---
        game.update();
        game.render();
    }

    return 0;
}