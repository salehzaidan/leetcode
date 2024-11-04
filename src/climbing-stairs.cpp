#include <gtest/gtest.h>

using namespace std;

class Solution1 {
  public:
    int climbStairs(int n) {
        vector<int> dp(n + 1);
        dp[0] = 1;
        dp[1] = 1;

        for (int i = 2; i <= n; i++) {
            dp[i] = dp[i - 1] + dp[i - 2];
        }

        return dp[n];
    }
};

class Solution1Test : public ::testing::Test {
  protected:
    Solution1 solution;
};

TEST_F(Solution1Test, TestCase1) {
    int n = 2;

    int actual = solution.climbStairs(n);
    int expected = 2;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase2) {
    int n = 3;

    int actual = solution.climbStairs(n);
    int expected = 3;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase3) {
    int n = 45;

    int actual = solution.climbStairs(n);
    int expected = 1836311903;

    EXPECT_EQ(actual, expected);
}