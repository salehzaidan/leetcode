#include <gtest/gtest.h>
#include <numeric>
#include <vector>

using namespace std;

class Solution1 {
  public:
    bool canPartition(vector<int> &nums) {
        int total = accumulate(nums.begin(), nums.end(), 0);
        if (total % 2 == 1) {
            return false;
        }

        int n = total / 2;
        vector<bool> dp(n + 1, false);
        dp[0] = true;

        for (int num : nums) {
            for (int i = n; i >= num; i--) {
                if (i - num >= 0 && dp[i - num]) {
                    dp[i] = true;
                }
            }
        }

        return dp[n];
    }
};

class Solution1Test : public ::testing::Test {
  protected:
    Solution1 solution;
};

TEST_F(Solution1Test, TestCase1) {
    vector<int> nums = {1, 5, 11, 5};

    bool actual = solution.canPartition(nums);
    bool expected = true;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase2) {
    vector<int> nums = {1, 2, 3, 5};

    bool actual = solution.canPartition(nums);
    bool expected = false;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase3) {
    vector<int> nums = {2, 2, 2, 2};

    bool actual = solution.canPartition(nums);
    bool expected = true;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase4) {
    vector<int> nums = {1, 1};

    bool actual = solution.canPartition(nums);
    bool expected = true;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase5) {
    vector<int> nums = {1};

    bool actual = solution.canPartition(nums);
    bool expected = false;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase6) {
    vector<int> nums = {1, 2, 5};

    bool actual = solution.canPartition(nums);
    bool expected = false;

    EXPECT_EQ(actual, expected);
}