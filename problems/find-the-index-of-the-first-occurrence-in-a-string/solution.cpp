#include <gtest/gtest.h>

using namespace std;

class Solution {
  public:
    int strStr(string haystack, string needle) {
        auto n = needle.size();
        for (size_t i = 0; i + n <= haystack.size(); i++) {
            string window(haystack.begin() + i, haystack.begin() + i + n);
            if (window == needle) {
                return i;
            }
        }

        return -1;
    }
};

TEST(Solution, StrStr1) {
    Solution solution;
    int expected = 0;
    int actual = solution.strStr("sadbutsad", "sad");
    EXPECT_EQ(expected, actual);
}

TEST(Solution, StrStr2) {
    Solution solution;
    int expected = -1;
    int actual = solution.strStr("leetcode", "leeto");
    EXPECT_EQ(expected, actual);
}

TEST(Solution, StrStr3) {
    Solution solution;
    int expected = 0;
    int actual = solution.strStr("a", "a");
    EXPECT_EQ(expected, actual);
}

