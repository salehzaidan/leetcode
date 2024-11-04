#include <gtest/gtest.h>
#include <vector>

using namespace std;

class Solution1 {
  public:
    int rob(vector<int> &nums) {
        int n = nums.size();
        if (n < 2) {
            return nums[0];
        }

        vector<int> dp(n);
        dp[0] = nums[0];
        dp[1] = max(dp[0], nums[1]);

        for (int i = 2; i < n; i++) {
            dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
        }

        return dp[n - 1];
    }
};

class Solution1Test : public ::testing::Test {
  protected:
    Solution1 solution;
};

TEST_F(Solution1Test, TestCase1) {
    vector<int> nums = {1, 2, 3, 1};

    int actual = solution.rob(nums);
    int expected = 4;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase2) {
    vector<int> nums = {2, 7, 9, 3, 1};

    int actual = solution.rob(nums);
    int expected = 12;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase3) {
    vector<int> nums = {400};

    int actual = solution.rob(nums);
    int expected = 400;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase4) {
    vector<int> nums = {1, 2};

    int actual = solution.rob(nums);
    int expected = 2;

    EXPECT_EQ(actual, expected);
}