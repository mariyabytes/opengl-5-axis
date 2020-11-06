#include "headers/game.h"

#include <chrono>

int main() {

    Game game("Learnin' Opengl",
              480, 480,
              4, 4,
              true);

    for (int i = 0; i < 20; i++) {
        game.initialRender();

    }



    auto start = std::chrono::high_resolution_clock::now();
    std::cout << "Calculating Depth map..." << std::endl;

    game.saveDepthMap();

    std::cout << "\t\t\t\t...Done" << std::endl;

    game.swapTorusAndBezier();
    game.calculateNearestPixel();

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