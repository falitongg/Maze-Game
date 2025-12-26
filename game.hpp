//
// Created by антін on 24/12/2025.
//

#ifndef CPPSEMESTRALPRJCT_GAME_HPP
#define CPPSEMESTRALPRJCT_GAME_HPP
#include "generator.hpp"
#include "maze.hpp"
#include "player.hpp"
#include "renderer.hpp"

class Game {
    private:
        Maze maze;
        Generator generator;
        Player player;
        Renderer renderer;
        bool isRunning;

        void handleInput();     //handles input from keyboard
        void update();          //changes player's position
        void render() const;    //asks Renderer to draw an updated map
    public:
        Game();
        //creates maze, player, isRunning = true
        void initialize();
        //game loop
        void run();

};

#endif //CPPSEMESTRALPRJCT_GAME_HPP