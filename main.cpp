#include "headers/game.h"

int main() {
    Game game("Learnin' Opengl",
              480, 480,
              4, 4,
              true);

//    std::cout << "Calculating Depth map..." << std::endl;
//
//    for (int i = 0; i < 100; i++) {
//        game.saveDepthMap();
//    }

//    std::cout << "\t\t\t... done." << std::endl;
//    game.rotateBezier();
//    game.removeBezier();
//    game.calculateNearestPixel();
    // std::cout << game.closestPixel << std::endl;

    //MAIN LOOP
    while (!game.getWindowShouldClose()) {

        //UPDATE INPUT ---
        game.update();
        game.render();
    }

    return 0;
}