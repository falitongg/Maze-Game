//
// Created by антін on 24/12/2025.
//
#include "game.hpp"

#include <iostream>
#include <conio.h>

Game::Game() : isRunning(false) {
}

void Game::initialize() {
    maze = Maze(10,10);

    for (int i = 1; i < 9; i++) {
        maze.setCell(i, 1, '.');  // horizontal corridor
        maze.setCell(8, i, '.');  // vertical corridor
    }

    maze.setExitCoordinates(8, 8);
    maze.setCell(8, 8, 'E');

    player = Player(1, 1);

    isRunning = true;
}

void Game::handleInput() {
    char input = _getch();
    // std::cin >> _getch();

    if (input == 'q' || input == 'Q') {
        isRunning = false;
    } else if (input == 'h') {
        renderer.showTutorial();
    }
    else {
        player.go(input, maze);
    }
}

void Game::update() {
    if (player.getX() == maze.getExitCoordinates().first && player.getY() == maze.getExitCoordinates().second) {
        std::cout << "\nCongratulations! You won\n";
        isRunning = false;
    }
}

void Game::render() const {
    renderer.draw(maze, player);
}


void Game::run() {
    while (isRunning) {
        render();
        handleInput();
        update();
    }
}
