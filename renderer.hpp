//
// Created by антін on 24/12/2025.
//

#ifndef CPPSEMESTRALPRJCT_RENDERER_HPP
#define CPPSEMESTRALPRJCT_RENDERER_HPP
#include <cstdlib>

#include "maze.hpp"
#include "player.hpp"

class Renderer {
    private:
        /**
         * @brief Clears screen
         */
        void clearScreen() const {
            #ifdef _WIN32
            std::system("cls");
            #else
                system("clear");
            #endif
        }
    public:
        Renderer();
        void draw(const Maze& maze, const Player& player) const;
        void showTutorial() const;
};

#endif //CPPSEMESTRALPRJCT_RENDERER_HPP