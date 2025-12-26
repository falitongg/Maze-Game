//
// Created by антін on 24/12/2025.
//

#ifndef CPPSEMESTRALPRJCT_GENERATOR_HPP
#define CPPSEMESTRALPRJCT_GENERATOR_HPP
#include "maze.hpp"
/**
 * @class Generator
 * @brief Generates random mazes using the recursive backtracking algorithm.
 *
 * The Generator operates directly on a Maze instance and carves passages
 * starting from a given starting cell. The resulting maze is a so‑called
 * "perfect maze" (there is exactly one path between any two cells).
 */
class Generator {
    private:
        /**
        * @brief Recursively carves passages in the maze.
        *
        * Marks the current cell as a passage and then visits neighbouring cells
        * in random order. For each unvisited neighbour that is within bounds,
        * it removes the wall between the current cell and the neighbour and
        * continues recursively from that neighbour.
        *
        * @param maze Reference to the maze being generated.
        * @param x Current cell x‑coordinate (column index).
        * @param y Current cell y‑coordinate (row index).
        */
        void carvePassages(Maze& maze, int x, int y);

    public:
        /**
         * @brief Default constructor.
         *
         * Creates an empty Generator instance ready to generate mazes.
         */
        Generator();

        /**
         * @brief Generates a maze starting from the given cell.
         *
         * Initializes the recursive backtracking algorithm from the starting
         * position. For correct behaviour of the algorithm, both @p startX
         * and @p startY should be odd coordinates that lie inside the maze.
         *
         * @param maze   Reference to the maze that will be filled with passages.
         * @param startX Starting cell x‑coordinate (should be odd).
         * @param startY Starting cell y‑coordinate (should be odd).
         */
        void generate(Maze& maze, int startX, int startY);

};

#endif //CPPSEMESTRALPRJCT_GENERATOR_HPP