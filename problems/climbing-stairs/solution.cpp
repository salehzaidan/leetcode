#include <gtest/gtest.h>
#include <vector>

using namespace std;

class Solution {
  public:
    int climbStairs(int n) {
        if (n <= 2) {
            return n;
        }

        vector<int> ways(n + 1);
        ways.at(1) = 1;
        ways.at(2) = 2;

        for (size_t i = 3; i <= n; i++) {
            ways.at(i) = ways.at(i - 1) + ways.at(i - 2);
        }

        return ways.at(n);
    }
};

TEST(Solution, ClimbStairs1) {
    Solution solution;
    int expected = 2;
    int actual = solution.climbStairs(2);
    EXPECT_EQ(expected, actual);
}

TEST(Solution, ClimbStairs2) {
    Solution solution;
    int expected = 3;
    int actual = solution.climbStairs(3);
    EXPECT_EQ(expected, actual);
}

TEST(Solution, ClimbStairs3) {
    Solution solution;
    int expected = 1;
    int actual = solution.climbStairs(1);
    EXPECT_EQ(expected, actual);
}
