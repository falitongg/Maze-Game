//
// Created by антін on 24/12/2025.
//
#include "game.hpp"
#include "player.hpp"
#include "renderer.hpp"
#include "generator.hpp"
#include <iostream>

Game::Game() : isRunning(false) {
}

void Game::initialize() {
    maze = Maze(91,21);
    generator = Generator();

    // for (int i = 1; i < 9; i++) {
    //     maze.setCell(i, 1, '.');  // horizontal corridor
    //     maze.setCell(8, i, '.');  // vertical corridor
    // }
    //
    // maze.setExitCoordinates(8, 8);
    // maze.setCell(8, 8, 'E');

    generator.generate(maze, 1, 1);

    player = Player(1, 1);

    isRunning = true;
}

void Game::handleInput() {
    char input;
    std::cin >> input;

    //uses only the first symbol entered
    while (std::cin.get() != '\n');

    if (input == 'q' || input == 'Q') {
        std::cout << "Quitting! Bye!" << std::endl;
        isRunning = false;
    } else if (input == 'h' || input == 'H') {
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
