//
// Created by антін on 24/12/2025.
//

#ifndef CPPSEMESTRALPRJCT_GENERATOR_HPP
#define CPPSEMESTRALPRJCT_GENERATOR_HPP
#include "maze.hpp"

class Generator {
    private:
        //cuts a passage in a maze
        void carvePassages(Maze& maze, int x, int y);
    public:
        Generator();
        //startX, startY % 2 != 0 for Backtracking algorithm
        void generate(Maze& maze, int startX, int startY);

};

#endif //CPPSEMESTRALPRJCT_GENERATOR_HPP