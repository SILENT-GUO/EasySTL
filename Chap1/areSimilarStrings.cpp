//
// Created by Zebin Guo on 12/10/24.
//

// 给两个字符串，判定他们重排后是否能一样
// 经典排序解决，或者哈希表
#include "areSimilarStrings.hpp"
#include "sort.hpp"


bool areSimilarStrings::areSimilarStrings1_2(String &s1, String &s2) {
    Sort::bubbleSort(s1);
    Sort::bubbleSort(s2);
    return s1.equals(s2);
}

