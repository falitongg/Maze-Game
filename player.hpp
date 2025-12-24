//
// Created by антін on 23/12/2025.
//

#ifndef CPPSEMESTRALPRJCT_PLAYER_HPP
#define CPPSEMESTRALPRJCT_PLAYER_HPP
#include <utility>

class Player {
    private:
        std::pair<int, int> currentPosition;
    public:
    //constructors
        Player();
        Player(int x, int y);
    //getters
        int getX() const;
        int getY() const;
        std::pair<int, int> getCurrentPosition() const;
    //setters
        void setX(int x);
        void setY(int y);
        void setCurrentPosition(int x, int y);
    //go function
        void go(char direction, const Maze& maze);
};


#endif //CPPSEMESTRALPRJCT_PLAYER_HPP