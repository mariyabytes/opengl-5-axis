#include "headers/game.h"

int main() {
    Game game("Learnin' Opengl",
              480, 480,
              4, 4,
              true);

    std::cout << "Calculating Depth map..." << std::endl;
    for (int i = 0; i < 20; i++) {
        game.initialRender();

    }
    std::cout << "\t\t\t\t...Done" << std::endl;
    game.saveDepthMap();

    game.swapTorusAndBezier();
    game.calculateNearestPixel();
    // std::cout << game.closestPixel << std::endl;

    //MAIN LOOP
    while (!game.getWindowShouldClose()) {

        //UPDATE INPUT ---
        game.update();
        game.render();
    }

    return 0;
}