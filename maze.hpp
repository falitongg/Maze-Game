//
// Created by антін on 23/12/2025.
//

#ifndef CPPSEMESTRALPRJCT_MAZE_HPP
#define CPPSEMESTRALPRJCT_MAZE_HPP
#include <utility>
#include <vector>

class Maze {
    private:
        std::pair<int, int> size;
        std::vector<std::vector<char>> maze;
        std::pair<int, int> exitCoordinates;
    public:
    //constructors
        Maze();
        Maze(int width, int height);
    //getters
        std::pair<int, int> getSize() const;
        std::pair<int, int> getExitCoordinates() const;
    //setters
        void setSize(int width, int height);
        void setExitCoordinates(int x, int y);
        void setWall(int x, int y, char value);
    //functions
        bool isInMazeBound  ds(int x, int y) const;
        bool isWall(int x, int y) const;
};

#endif //CPPSEMESTRALPRJCT_MAZE_HPP