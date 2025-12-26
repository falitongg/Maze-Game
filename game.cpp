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

char helloFunction() {
    std::cout << "Welcome to the game!\n";
    std::cout << "Choose preferred maze size :\n [1] - SMALL(31x15)\n [2] - MEDIUM(51x21)\n [3] - LARGE(101x21)\n [4] - custom size \n";
    std::cout << "Press H to show tutorial\n";
    std::cout << "Press number 1-4 and press Enter...\n";

    char input;

    while (true) {
        input = std::cin.get();
        while (std::cin.get() != '\n');
        if (input == '1' || input == '2' || input == '3' || input == '4') {
            break;
        }

        std::cout << "CHOOSE IT NOW\n";
    }

    return input;
}

std::pair<int, int> customChoice() {
    std::cin.clear();

    int width = 0;
    int height = 0;

    while (true) {
        std::cout << "Enter maze width (11-99): ";
        std::cin >> width;

        std::cout << "Enter maze height (11-99): ";
        std::cin >> height;

        bool tooWide  = width  >= 100;
        bool tooHigh  = height >= 100;
        bool hugeSquare = (width == height && width >= 60);

        if (std::cin.fail()) {
            // if user didnt enter int
            std::cin.clear();
            std::cin.ignore(10000, '\n');  // clears garbage
            std::cout << "Invalid input. Please enter positive integers.\n";
            continue;
        }

        if (tooWide || tooHigh || hugeSquare) {
            std::cout << "Too large size. Try smaller values.\n";
            continue;
        }
        if (width < 11 || height < 11) {
            std::cout << "Width and height must be at least 11. Try again.\n";
            continue;
        }

        break;
    }

    if (width % 2 == 0) {
        width += 1;
    }
    if (height % 2 == 0) {
        height += 1;
    }

    return {width, height};
}

void Game::initialize() {
    int width = 0;
    int height = 0;

    char choice = helloFunction();
    switch (choice) {
        case '1': width = 31; height = 15; break;
        case '2': width = 51; height = 21; break;
        case '3': width = 101; height = 21; break;
        case '4':{
            auto preferredSize = customChoice();
            width = preferredSize.first;
            height = preferredSize.second;
            break;
        };
    }

    maze = Maze(width,height);
    generator = Generator();

    // for (int i = 1; i < 9; i++) {
    //     maze.setCell(i, 1, '.');  // horizontal corridor
    //     maze.setCell(8, i, '.');  // vertical corridor
    // }
    //
    // maze.setExitCoordinates(8, 8);
    // maze.setCell(8, 8, 'E');

    generator.generate(maze, 1, 1);
    //sets exit at the end
    maze.setExitCoordinates(width - 2, height - 1);
    maze.setCell(width - 2, height - 1, 'E');

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
