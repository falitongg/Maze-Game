cmake_minimum_required(VERSION 4.0)
project(cppsemestralprjct)

set(CMAKE_CXX_STANDARD 20)

add_executable(cppsemestralprjct main.cpp
        player.hpp
        maze.hpp
        renderer.hpp
        game.hpp
        generator.hpp
)
