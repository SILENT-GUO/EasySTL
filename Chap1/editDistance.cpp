//
// Created by Zebin Guo on 12/12/24.
//

#include "editDistance.hpp"
#include "Vector.hpp"

// 给定字符串 a, b, 求使他们相等的最小编辑次数，作为最小距离
// 可以进行的操作：
// 删除一个字符，添加一个字符或者修改一个字符
// hint 删除和添加一个字符可以视为一种操作

int editDistance::minDistance(const String& a, const String& b) {
    const size_t size_a = a.size();
    const size_t size_b = b.size();
    // dp[i][j] is min distance of substring a[0:i] and substring b[0:j]
    // output dp[size_a][size_b]
    Vector dp(size_a+1, Vector(size_b+1, 0));
    dp[0][0] = 0;
    for(int i = 1; i <= size_a; i++) {
        dp[i][0] = i;
    }
    for(int j = 1; j <= size_b; j++) {
        dp[0][j] = j;
    }

    for(int i = 1; i <= size_a; i++) {
        for(int j = 1; j <= size_b; j++) {
            dp[i][j] = std::min(std::min(dp[i-1][j] + 1, dp[i][j-1] + 1), dp[i-1][j-1] + (a[i-1] == b[j-1] ? 0 : 1));
        }
    }
    return dp[size_a][size_b];
}

