cmake_minimum_required(VERSION 3.10.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)
project(wordHunt VERSION 0.1.0 LANGUAGES C CXX)
add_executable(wordHunt main.cpp trie.h trie.cpp boardSolver.h boardSolver.cpp)

