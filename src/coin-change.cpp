#include <gtest/gtest.h>
#include <limits>
#include <vector>

using namespace std;

class Solution1 {
  public:
    int coinChange(vector<int> &coins, int amount) {
        const int inf = numeric_limits<int>::max();
        vector<int> dp(amount + 1, inf);

        dp[0] = 0;
        for (int coin : coins) {
            if (coin <= amount) {
                dp[coin] = 1;
            }
        }

        for (int i = 1; i <= amount; i++) {
            int q = dp[i];

            for (int coin : coins) {
                if (i - coin >= 0) {
                    q = min(q, dp[i - coin]);
                }
            }

            if (q != inf) {
                dp[i] = q + 1;
            }
        }

        return dp[amount] == inf ? -1 : dp[amount];
    }
};

class Solution1Test : public ::testing::Test {
  protected:
    Solution1 solution;
};

TEST_F(Solution1Test, TestCase1) {
    vector<int> coins = {1, 2, 5};
    int amount = 11;

    int actual = solution.coinChange(coins, amount);
    int expected = 3;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase2) {
    vector<int> coins = {2};
    int amount = 3;

    int actual = solution.coinChange(coins, amount);
    int expected = -1;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase3) {
    vector<int> coins = {1};
    int amount = 0;

    int actual = solution.coinChange(coins, amount);
    int expected = 0;

    EXPECT_EQ(actual, expected);
}