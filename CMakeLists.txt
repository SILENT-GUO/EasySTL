cmake_minimum_required(VERSION 3.30)
project(CC189)

set(CMAKE_CXX_STANDARD 20)

add_executable(CC189 main.cpp Chap1/isCharacterUnique.cpp
        Chap1/areSimilarStrings.cpp
        Headers/areSimilarStrings.hpp
)

target_include_directories(CC189 PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Container
        ${CMAKE_CURRENT_SOURCE_DIR}/Utils
        ${CMAKE_CURRENT_SOURCE_DIR}/Headers
)
