#include <gtest/gtest.h>

using namespace std;

class Solution {
  public:
    bool isPalindrome(int x) {
        long y = 0L;
        auto tmp = x;
        while (tmp > 0) {
            y = y * 10 + tmp % 10;
            tmp /= 10;
        }
        return x == y;
    }
};

TEST(Solution, IsPalindrome1) {
    Solution solution;
    bool expected = true;
    bool actual = solution.isPalindrome(121);
    EXPECT_EQ(expected, actual);
}

TEST(Solution, IsPalindrome2) {
    Solution solution;
    bool expected = false;
    bool actual = solution.isPalindrome(-121);
    EXPECT_EQ(expected, actual);
}

TEST(Solution, IsPalindrome3) {
    Solution solution;
    bool expected = false;
    bool actual = solution.isPalindrome(10);
    EXPECT_EQ(expected, actual);
}

TEST(Solution, IsPalindrome4) {
    Solution solution;
    bool expected = false;
    bool actual = solution.isPalindrome(1234567899);
    EXPECT_EQ(expected, actual);
}

