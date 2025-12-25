#include "game.hpp"
#include "helper.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc > 1) {
        std::string arg = argv[1];
        if (arg == "--help") {
            printHelp();
            return 0;
        }
    }
    Game game;
    game.initialize();
    game.run();
    return 0;
}