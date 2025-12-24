//
// Created by антін on 23/12/2025.
//

#ifndef CPPSEMESTRALPRJCT_MAZE_HPP
#define CPPSEMESTRALPRJCT_MAZE_HPP
#include <utility>
#include <vector>

/**
 * @class Maze
 * @brief Represents a maze structure
 *
 * This class manages the maze structure, including its size, walls, passages, and exit coordinates.
 * It provides methods to check boundaries and wall positions
 */
class Maze {
    private:
        std::pair<int, int> size;                       ///< Width and height of the maze
        std::vector<std::vector<char>> maze;            ///< 2D grid representing the maze structure
        std::pair<int, int> exitCoordinates;            ///< Coordinates of the maze exit
    public:
    //constructors
        Maze();

        /**
         * @brief Constructs a maze with specified dimesnions
         * @param width The width of the maze
         * @param height The height of the maze
         */
        Maze(int width, int height);
    //getters
        /**
         * @brief Gets the size of the maze
         * @return A pair containing width and height
         */
        std::pair<int, int> getSize() const;

        /**
         * @brief  Gets the exit coordinates
         * @return A pair containing x and y coordinates of the exit
         */
        std::pair<int, int> getExitCoordinates() const;

        /**
         * @brief Gets a cell value at the specified position
         * @param x X-coordinate
         * @param y Y-coordinate
         * @return
         */
        char getCell(int x, int y) const;
    //setters
        void setSize(int width, int height);
        void setExitCoordinates(int x, int y);

        /**
         * @brief Sets a cell value at the specified position
         * @param x X-coordinate
         * @param y Y-coordinate
         * @param value Character representing the cell  (e.g., "#" for wall, "." for passage)
         */
        void setCell(int x, int y, char value);
    //functions
        /**
         * @brief Checks if coordinates are within maze bounds.
         * @param x X-coordinate to check
         * @param y Y-coordinate to check
         * @return true if coordinates are inside the maze, false otherwise
         */
        bool isInMazeBounds(int x, int y) const;
        /**
        * @brief Checks if a cell is a wall.
        * @param x X-coordinate
        * @param y Y-coordinate
        * @return true if the cell is a wall, false otherwise
        */
        bool isWall(int x, int y) const;
};

#endif //CPPSEMESTRALPRJCT_MAZE_HPP