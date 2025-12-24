//
// Created by антін on 24/12/2025.
//

#ifndef CPPSEMESTRALPRJCT_RENDERER_HPP
#define CPPSEMESTRALPRJCT_RENDERER_HPP
#include "maze.hpp"
#include "player.hpp"

class Renderer {
    public:
        Renderer();
        void draw(const Maze& maze, const Player& player) const;
        void showTutorial() const;
};

#endif //CPPSEMESTRALPRJCT_RENDERER_HPP