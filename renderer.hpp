//
// Created by антін on 24/12/2025.
//

#ifndef CPPSEMESTRALPRJCT_RENDERER_HPP
#define CPPSEMESTRALPRJCT_RENDERER_HPP
#define ANSI_CLEAR  "\x1B[2J\x1B[H"

#include <iostream>

#include "maze.hpp"
#include "player.hpp"

class Renderer {
    private:
        /**
         * @brief Clears screen
         */
        void clearScreen() const {
            std::cout << ANSI_CLEAR <<std::flush;
        }
    public:
        Renderer();
        void draw(const Maze& maze, const Player& player) const;

        char showTutorial() const;
};

#endif //CPPSEMESTRALPRJCT_RENDERER_HPP