//
// Created by антін on 24/12/2025.
//

#include "player.hpp"
#include "maze.hpp"

Player::Player() : currentPosition(std::make_pair(0, 0)) {
}

Player::Player(int x, int y) : currentPosition(std::make_pair(x, y)) {
}

int Player::getX() const {
    return currentPosition.first;
}

int Player::getY() const {
    return currentPosition.second;
}

std::pair<int, int> Player::getCurrentPosition() const {
    return currentPosition;
}

void Player::setCurrentPosition(int x, int y) {
    currentPosition = std::make_pair(x, y);
}

void Player::go(char direction, const Maze& maze) {
    int newX = getX();
    int newY = getY();
    switch (direction) {
        case 'w': case 'W': newY = getY() - 1; break;
        case 's': case 'S': newY = getY() + 1; break;
        case 'a': case 'A': newX = getX() - 1; break;
        case 'd': case 'D': newX = getX() + 1; break;
        default: return;
    }
    if (maze.isInMazeBounds(newX, newY) && !maze.isWall(newX, newY)) {
        setCurrentPosition(newX, newY);
    }
}

