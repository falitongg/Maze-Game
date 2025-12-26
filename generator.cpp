//
// Created by антін on 25/12/2025.
//
#include "generator.hpp"
#include "vector"
#include "algorithm"
#include "random"

Generator::Generator() {

}

void Generator::generate(Maze &maze, int startX, int startY) {
    carvePassages(maze, startX, startY);
}
//changes '#' to '.' in (x,y) and chooses a random not visited neighbour (coordinate_axis + 2)
//and then in ny,nx breaks a wall
void Generator::carvePassages(Maze &maze, int x, int y) {
    maze.setCell(x, y, '.');

    std::vector<std::pair<int, int>> directions = {
        {0, -2},    //up
        {0, 2},     //down
        {-2, 0},    //left
        {2,0}       //right
    };

    //shuffle vector of directions
    std::random_device rd;
    std::mt19937 gen(rd());

    std::shuffle(directions.begin(), directions.end(), gen);

    //chooses random directions
    for (const auto& direction : directions) {
        int dx = direction.first;
        int dy = direction.second;

        int nx = x + dx;
        int ny = y + dy;

        if (maze.isInMazeBounds(nx, ny) && maze.getCell(nx, ny) == '#') {
            maze.setCell((x + nx)/2, (y + ny)/2, '.');
            carvePassages(maze, nx, ny);
        }
    }


}
