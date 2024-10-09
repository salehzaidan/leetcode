#include <gtest/gtest.h>

using namespace std;

class Solution1 {
public:
  int maxProfit(const vector<int> &prices) {
    int left = 0;
    int right = 0;
    int profit = 0;
    while (right < prices.size()) {
      if (prices[right] < prices[left]) {
        left = right;
        continue;
      }

      profit = max(profit, prices[right] - prices[left]);
      right++;
    }

    return profit;
  }
};

class Solution1Test : public ::testing::Test {
protected:
  Solution1 solution;
};

TEST_F(Solution1Test, TestCase1) {
  vector<int> prices = {7, 1, 5, 3, 6, 4};

  int actual = solution.maxProfit(prices);
  int expected = 5;

  EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase2) {
  vector<int> prices = {7, 6, 4, 3, 1};

  int actual = solution.maxProfit(prices);
  int expected = 0;

  EXPECT_EQ(actual, expected);
}