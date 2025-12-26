//
// Created by антін on 25/12/2025.
//

/**
 * @file generator.cpp
 * @brief Implementation of the maze generator based on recursive backtracking.
 *
 * This module provides the implementation of the Generator class which
 * carves a random perfect maze by recursively visiting cells and removing
 * walls between them.
 */
#include "generator.hpp"

#include "vector"
#include "algorithm"
#include "random"

/**
 * @brief Default constructor.
 *
 * Initializes an empty Generator object ready for maze generation.
 */
Generator::Generator() {

}

void Generator::generate(Maze &maze, int startX, int startY) {
    // Start recursive backtracking from the given starting cell.
    carvePassages(maze, startX, startY);
}

/**
 * @brief Recursively carves passages from a given cell.
 *
 * The algorithm:
 *  - marks the current cell as a passage ('.'),
 *  - creates a list of four possible directions (up, down, left, right),
 *  - shuffles the directions randomly,
 *  - for each direction computes the neighbour two cells away,
 *  - if the neighbour is inside the maze and still a wall ('#'),
 *    removes the wall between current cell and the neighbour and
 *    continues recursively from the neighbour.
 *
 * This produces a connected maze with no cycles (perfect maze).
 *
 * @param maze Reference to the maze being modified.
 * @param x    Current cell x‑coordinate.
 * @param y    Current cell y‑coordinate.
 */
void Generator::carvePassages(Maze &maze, int x, int y) {
    // Mark current cell as a passage.
    maze.setCell(x, y, '.');

    // Relative moves: up, down, left, right (two cells away).
    std::vector<std::pair<int, int>> directions = {
        {0, -2},    //up
        {0, 2},     //down
        {-2, 0},    //left
        {2,0}       //right
    };

    // Shuffle directions to randomize maze structure.
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(directions.begin(), directions.end(), gen);

    // Try all directions in random order.
    for (const auto& direction : directions) {
        int dx = direction.first;
        int dy = direction.second;

        int nx = x + dx;
        int ny = y + dy;

        // If neighbour is inside the maze and still a wall,
        // remove the wall between (x,y) and (nx,ny) and recurse.
        if (maze.isInMazeBounds(nx, ny) && maze.getCell(nx, ny) == '#') {
            int wx = (x + nx) / 2;  // wall x between current cell and neighbour
            int wy = (y + ny) / 2;  // wall y between current cell and neighbour
            maze.setCell(wx, wy, '.');

            carvePassages(maze, nx, ny);
        }
    }


}
