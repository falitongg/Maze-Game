//
// Created by антін on 24/12/2025.
//

/**
 * @file maze.cpp
 * @brief Implementation of the Maze class.
 *
 * Provides constructors and member functions to manipulate the internal
 * 2D grid of the maze, including size management, cell access and
 * boundary checks.
 */

#include "maze.hpp"
#include <utility>
#include <vector>

Maze::Maze() : size(50, 50) {
    // Default maze filled entirely with walls ('#').
    maze.resize(size.second, std::vector<char>(size.first, '#'));
}

Maze::Maze(int width, int height) :size(width, height) {
    // Initialize maze grid with given dimensions and fill with walls.
    maze.resize(size.second, std::vector<char>(size.first, '#'));
}

std::pair<int, int> Maze::getSize() const {
    return size;
}

std::pair<int, int> Maze::getExitCoordinates() const {
    return exitCoordinates;
}

char Maze::getCell(int x, int y) const {
    if (isInMazeBounds(x, y)) {
        return maze[y][x];
    }
    // Default return value for out-of-bounds access.
    return '#';
}

void Maze::setSize(int width, int height) {
    size = std::make_pair(width, height);
    // Resize and reset all cells to walls.
    maze.resize(size.second, std::vector<char>(size.first, '#'));
}

void Maze::setExitCoordinates(int x, int y) {
    exitCoordinates = std::make_pair(x, y);
}

void Maze::setCell(int x, int y, char value) {
    if (isInMazeBounds(x, y)) {
        maze[y][x] = value;
    }
}

bool Maze::isInMazeBounds(int x, int y) const {
    if (x < 0 || x >= size.first || y < 0 || y >= size.second) {
        return false;
    }
    return true;
}

bool Maze::isWall(int x, int y) const {
    if (isInMazeBounds(x, y)) {
        return maze[y][x] == '#';
    }
    return false;
}
