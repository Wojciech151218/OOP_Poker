cmake_minimum_required(VERSION 3.28)
project(OOP_Poker)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add executable target
add_executable(OOP_Poker
        main.cpp
        source/Card.cpp
        source/Deck.cpp
        source/GameState.cpp
        source/Action.cpp
        source/Hand.cpp
        source/Player.cpp
        source/UserInterface.cpp)

# Include the Crow library and headers directory
target_include_directories(OOP_Poker PRIVATE
        ${CMAKE_SOURCE_DIR}/Crow
        ${CMAKE_SOURCE_DIR}/headers)

# Link pthread for multithreading
target_link_libraries(OOP_Poker PRIVATE pthread)
