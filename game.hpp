//
// Created by антін on 24/12/2025.
//

#ifndef CPPSEMESTRALPRJCT_GAME_HPP
#define CPPSEMESTRALPRJCT_GAME_HPP
#include "generator.hpp"
#include "maze.hpp"
#include "player.hpp"
#include "renderer.hpp"

/**
 * @class Game
 * @brief High-level controller of the maze game.
 *
 * The Game class owns all main components (Maze, Generator, Player, Renderer)
 * and manages the game loop. It is responsible for initializing the game
 * state, handling user input, updating the game logic and rendering the maze.
 */
class Game {
    private:
        /// Maze currently being played.
        Maze maze;

        /// Maze generator implementing recursive backtracking.
        Generator generator;

        /// Player controlled by the user.
        Player player;

       /// Renderer responsible for drawing the maze and player.
        Renderer renderer;

        /// Flag indicating whether the main game loop should continue running.
        bool isRunning;

        /**
         * @brief Reads and processes a single user input command.
         *
         * Handles quitting the game, showing the tutorial, or moving the player
         * in the maze according to the input character.
         */
        void handleInput();     //handles input from keyboard

        /**
         * @brief Updates the game state after a user action.
         *
         * Currently, checks whether the player has reached the exit cell and
         * stops the game if the maze is solved.
         */
        void update();

        /**
         * @brief Renders the current game state to the terminal.
         *
         * Delegates drawing to the Renderer instance, which prints the maze
         * and the player's position.
         */
        void render() const;    //asks Renderer to draw an updated map

    public:
        /**
         * @brief Constructs a Game object with an initial stopped state.
         *
         * The actual maze, player and generator are set up in initialize().
         */
        Game();

        /**
         * @brief Initializes the game before the main loop starts.
         *
         * Shows a menu that lets the user choose a predefined maze size or
         * enter a custom size, then:
         *  - creates a Maze of the chosen dimensions,
         *  - generates a random maze using the Generator,
         *  - places the exit and the player,
         *  - sets @c isRunning to true.
         */
        void initialize();

        /**
         * @brief Runs the main game loop.
         *
         * As long as @c isRunning is true, the loop repeatedly renders the
         * maze, handles user input and updates the game state.
         */
        void run();

};

#endif //CPPSEMESTRALPRJCT_GAME_HPP