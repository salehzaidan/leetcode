#include <gtest/gtest.h>
#include <vector>

using namespace std;

class Solution1 {
  public:
    int minCostClimbingStairs(vector<int> &cost) {
        int n = cost.size();
        vector<int> dp(n + 1);
        dp[0] = 0;
        dp[1] = 0;

        for (int i = 2; i <= n; i++) {
            dp[i] = min(cost[i - 1] + dp[i - 1], cost[i - 2] + dp[i - 2]);
        }

        return dp[n];
    }
};

class Solution1Test : public ::testing::Test {
  protected:
    Solution1 solution;
};

TEST_F(Solution1Test, TestCase1) {
    vector<int> cost = {10, 15, 20};

    int actual = solution.minCostClimbingStairs(cost);
    int expected = 15;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase2) {
    vector<int> cost = {1, 100, 1, 1, 1, 100, 1, 1, 100, 1};

    int actual = solution.minCostClimbingStairs(cost);
    int expected = 6;

    EXPECT_EQ(actual, expected);
}