//
// Created by антін on 25/12/2025.
//

/**
 * @file helper.cpp
 * @brief Implementation of small helper utilities for the game.
 *
 * Currently, contains only the printHelp() function that prints a brief
 * description of controls and the game goal.
 */

#include "helper.hpp"
#include <iostream>

void printHelp() {
    std::cout << "Player's position: '@'\n";
    std::cout << "Controls: W/A/S/D - move, Q - quit, help - 'H'\n";
    std::cout << "Reach the exit 'E' to win!\n\n";
}
