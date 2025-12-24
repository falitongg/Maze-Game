//
// Created by антін on 24/12/2025.
//

#include "maze.hpp"

Maze::Maze() : size(50, 50) {
    maze.resize(size.second, std::vector<char>(size.first, '#'));
}

Maze::Maze(int width, int height) :size(width, height) {
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
    return '#';     //default return
}

void Maze::setSize(int width, int height) {
    size = std::make_pair(width, height);
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
