#include <iostream>
#include "Vector.hpp"
#include "sort.hpp"
#include "String.hpp"

#include "Headers/1-unique_characters.hpp"

void run_sort_tests();
void run_vector_tests();
void run_chap1_tests();

int main(int argc, char *argv[]) {
    if (argc == 2 && std::string(argv[1]) == "--sort") {
        run_sort_tests();
    } else if (argc == 2 && std::string(argv[1]) == "--vector") {
        run_vector_tests();
    } else if (argc == 2 && std::string(argv[1]) == "--chap1") {
        run_chap1_tests();
    }


    else {
        std::cerr << "Usage: " << argv[0] << " --sort" << std::endl;
    }

    return 0;
}


void run_sort_tests() {
    Vector<int> vec = {5, 3, 8, 1, 2};
    Sort::bubbleSort(vec);
    std::cout << "Using bubbleSort" << std::endl;
    for (const auto& num : vec) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    std::cout << "Using selectionSort" << std::endl;
    Sort::selectionSort(vec);
    for (const auto& num : vec) {
        std::cout << num << " ";
    }
}

void run_vector_tests() {
    Vector<int> vec = {5, 3, 8, 1, 2};
    vec.push_back(3);
    vec.push_back(8);
    vec.push_back(2);
    for (const auto& num : vec) {
        std::cout << num << " ";
    }
}

void run_chap1_tests() {
    String s1("hello world");
    std::cout << "Problem 1: " << std::endl;
    std::cout << "--------" << std::endl;
    std::cout << "Input: " << s1.data() << " - " << "Output: " << isCharacterUnique::isCharacterUnique_1_1(s1) << std::endl;
}