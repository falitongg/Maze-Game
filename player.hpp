//
// Created by антін on 23/12/2025.
//

#ifndef CPPSEMESTRALPRJCT_PLAYER_HPP
#define CPPSEMESTRALPRJCT_PLAYER_HPP

#include <utility>
#include "maze.hpp"

/**
 * @class Player
 * @brief Represents the player in the maze.
 *
 * The Player stores its current position as grid coordinates and provides
 * methods to query and update this position. Movement is constrained by
 * the Maze: the player cannot leave the bounds or walk through walls.
 */
class Player {
private:
    std::pair<int,int> currentPosition; ///< Current (x, y) coordinates of the player.

public:
    // constructors

    /**
     * @brief Default constructor.
     *
     * Initializes the player at position (0, 0).
     */
    Player();

    /**
     * @brief Constructs a player at a given position.
     * @param x Initial x‑coordinate.
     * @param y Initial y‑coordinate.
     */
    Player(int x, int y);

    // getters

    /**
     * @brief Gets the current x‑coordinate of the player.
     * @return Current x‑coordinate.
     */
    int getX() const;

    /**
     * @brief Gets the current y‑coordinate of the player.
     * @return Current y‑coordinate.
     */
    int getY() const;

    /**
     * @brief Gets the current player position as a pair.
     * @return Pair (x, y) with current coordinates.
     */
    std::pair<int,int> getCurrentPosition() const;

    // setters

    /**
     * @brief Sets the current position of the player.
     * @param x New x‑coordinate.
     * @param y New y‑coordinate.
     */
    void setCurrentPosition(int x, int y);

    /**
     * @brief Moves the player in the maze according to a direction key.
     *
     * Interprets the given character as one of the movement commands:
     *  - 'W'/'w' – up,
     *  - 'S'/'s' – down,
     *  - 'A'/'a' – left,
     *  - 'D'/'d' – right.
     *
     * The player is only moved if the target cell is inside the maze
     * and is not a wall. Any other character is ignored.
     *
     * @param direction Character representing the move command.
     * @param maze      Constant reference to the Maze used for bounds
     *                  and wall checks.
     */
    void go(char direction, const Maze& maze);
};

#endif //CPPSEMESTRALPRJCT_PLAYER_HPP
