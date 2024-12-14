// 实现算法，确定一个字符串的所有字符都不相同，不允许使用额外数据结构
#include "sort.hpp"
#include "isCharacterUnique.hpp"


bool isCharacterUnique::isCharacterUnique_1_1(String &s) {
  Sort::selectionSort(s);
  for (int i = 1; i < s.size(); i++) {
    if (s[i] == s[i - 1]) {
      return true;
    }
  }
  return false;
}
