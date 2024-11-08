#include <gtest/gtest.h>
#include <vector>

using namespace std;

class Solution1 {
  public:
    int lengthOfLIS(vector<int> &nums) {
        int n = nums.size();
        vector<int> dp(n);
        dp[0] = 1;

        int maxLength = dp[0];

        for (int i = 1; i < n; i++) {
            int q = 0;

            for (int j = 0; j < i; j++) {
                if (nums[i] > nums[j]) {
                    q = max(q, dp[j]);
                }
            }

            dp[i] = q + 1;
            maxLength = max(maxLength, dp[i]);
        }

        return maxLength;
    }
};

class Solution1Test : public ::testing::Test {
  protected:
    Solution1 solution;
};

TEST_F(Solution1Test, TestCase1) {
    vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};

    int actual = solution.lengthOfLIS(nums);
    int expected = 4;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase2) {
    vector<int> nums = {0, 1, 0, 3, 2, 3};

    int actual = solution.lengthOfLIS(nums);
    int expected = 4;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase3) {
    vector<int> nums = {7, 7, 7, 7, 7, 7, 7};

    int actual = solution.lengthOfLIS(nums);
    int expected = 1;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase4) {
    vector<int> nums = {1};

    int actual = solution.lengthOfLIS(nums);
    int expected = 1;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase5) {
    vector<int> nums = {9, 8, 7, 6, 5};

    int actual = solution.lengthOfLIS(nums);
    int expected = 1;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase6) {
    vector<int> nums = {1, 2, 3, 4, 5};

    int actual = solution.lengthOfLIS(nums);
    int expected = 5;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase7) {
    vector<int> nums = {10, 9, 10, 11, 12};

    int actual = solution.lengthOfLIS(nums);
    int expected = 4;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase8) {
    vector<int> nums = {4, 10, 4, 3, 8, 9};

    int actual = solution.lengthOfLIS(nums);
    int expected = 3;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase9) {
    vector<int> nums = {1, 3, 6, 7, 9, 4, 10, 5, 6};

    int actual = solution.lengthOfLIS(nums);
    int expected = 6;

    EXPECT_EQ(actual, expected);
}