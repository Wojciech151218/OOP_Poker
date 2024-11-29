cmake_minimum_required(VERSION 3.28)
project(OOP_Poker)

set(CMAKE_CXX_STANDARD 17)

add_executable(OOP_Poker main.cpp
        headers/utils.h
        source/Card.cpp
        headers/Card.h
        source/Deck.cpp
        headers/Deck.h
        source/GameState.cpp
        headers/GameState.h
        source/Action.cpp
        headers/Action.h
        source/Hand.cpp
        headers/Hand.h
        source/Player.cpp
        headers/Player.h
        source/UserInterface.cpp
        headers/UserInterface.h)
