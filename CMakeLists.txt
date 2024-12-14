cmake_minimum_required(VERSION 3.30)
project(CC189)

set(CMAKE_CXX_STANDARD 20)

add_executable(CC189 main.cpp Chap1/isCharacterUnique.cpp
        Chap1/areSimilarStrings.cpp
        Chap1/subStringReplacement.cpp
        Chap1/editDistance.cpp
        Headers/editDistance.hpp
        Chap1/stringCompression.cpp
        Headers/stringCompression.hpp
        Chap1/MatrixRotation.cpp
        Headers/MatrixRotation.hpp
        Container/SingleLinkedList.hpp
)

target_include_directories(CC189 PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Container
        ${CMAKE_CURRENT_SOURCE_DIR}/Utils
        ${CMAKE_CURRENT_SOURCE_DIR}/Headers
)
