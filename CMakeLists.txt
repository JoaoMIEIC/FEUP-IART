cmake_minimum_required(VERSION 3.21)
project(ProjIART)

set(CMAKE_CXX_STANDARD 14)

add_executable(ProjIART main.cpp files.cpp street.cpp car.cpp intersection.cpp evaluation.cpp algorithms.cpp genetic.cpp)
