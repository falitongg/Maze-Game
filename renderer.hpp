//
// Created by антін on 24/12/2025.
//

#ifndef CPPSEMESTRALPRJCT_RENDERER_HPP
#define CPPSEMESTRALPRJCT_RENDERER_HPP

#define ANSI_CLEAR "\x1B[2J\x1B[H"

#include <iostream>
#include "maze.hpp"
#include "player.hpp"

/**
 * @class Renderer
 * @brief Handles console output for the maze game.
 *
 * Uses ANSI escape sequences to clear screen and render the maze grid
 * with the player position overlaid. Also displays the help/tutorial.
 */
class Renderer {
private:
    /**
     * @brief Clears the terminal screen using ANSI escape sequence.
     *
     * Sends the standard ANSI clear screen and move cursor to top-left
     * sequence: ESC[2J ESC[H.
     */
    void clearScreen() const {
        std::cout << ANSI_CLEAR << std::flush;
    }

public:
    /**
     * @brief Default constructor. No initialization required.
     */
    Renderer();

    /**
     * @brief Draws the complete maze with player position.
     *
     * Clears screen first, then iterates through maze cells. Overlays
     * the player '@' symbol on their current position. Other cells show
     * their maze character ('#', '.', 'E', etc.).
     *
     * @param maze   Const reference to the maze grid.
     * @param player Const reference to the player position.
     */
    void draw(const Maze &maze, const Player &player) const;

    /**
     * @brief Shows the game tutorial/help screen.
     *
     * Clears screen, prints help text using printHelp(), then waits
     * for Enter key press before returning.
     */
    void showTutorial() const;
};

#endif //CPPSEMESTRALPRJCT_RENDERER_HPP
