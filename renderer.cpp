//
// Created by антін on 24/12/2025.
//

/**
 * @file renderer.cpp
 * @brief Implementation of the Renderer class.
 *
 * Renders the maze game state to console using ANSI sequences for
 * screen clearing and efficient text output.
 */

#include "renderer.hpp"
#include "helper.hpp"
#include <iostream>

Renderer::Renderer() {
    // No special initialization required.
}

void Renderer::draw(const Maze &maze, const Player &player) const {
    clearScreen();

    // Render maze row by row, overlaying player position.
    for (int y = 0; y < maze.getSize().second; y++) {
        for (int x = 0; x < maze.getSize().first; x++) {
            if (player.getX() == x && player.getY() == y) {
                std::cout << '@';
            } else {
                std::cout << maze.getCell(x, y);
            }
        }
        std::cout << '\n';
    }
}

void Renderer::showTutorial() const {
    clearScreen();
    printHelp();
    std::cout << "Press Enter to continue...\n";
    std::cin.get();
}
