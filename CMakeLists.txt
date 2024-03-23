cmake_minimum_required(VERSION 3.26)
project(Challenge_1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Challenge_1
        Amijo.cpp
        Amijo.hpp
        gradient.cpp
        gradient.hpp
        InverseDecay.cpp
        InverseDecay.hpp
        main.cpp
        Method.hpp
        UpdateRule.hpp
        vector.hpp
        vector.cpp
        ExponentialDecay.hpp
        ExponentialDecay.cpp
        main_readfromfile.cpp)
