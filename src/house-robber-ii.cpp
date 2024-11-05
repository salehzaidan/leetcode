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

        return max(rob(nums.begin(), nums.begin() + n - 1),
                   rob(nums.begin() + 1, nums.begin() + n));
    }

  private:
    int rob(vector<int>::const_iterator begin,
            vector<int>::const_iterator end) {
        int n = distance(begin, end);
        if (n < 2) {
            return *begin;
        }

        vector<int> dp(n);
        dp[0] = *begin;
        dp[1] = max(dp[0], *(begin + 1));

        for (int i = 2; i < n; i++) {
            dp[i] = max(dp[i - 1], dp[i - 2] + *(begin + i));
        }

        return dp[n - 1];
    }
};

class Solution1Test : public ::testing::Test {
  protected:
    Solution1 solution;
};

TEST_F(Solution1Test, TestCase1) {
    vector<int> nums = {2, 3, 2};

    int actual = solution.rob(nums);
    int expected = 3;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase2) {
    vector<int> nums = {1, 2, 3, 1};

    int actual = solution.rob(nums);
    int expected = 4;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase3) {
    vector<int> nums = {1, 2, 3};

    int actual = solution.rob(nums);
    int expected = 3;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase4) {
    vector<int> nums = {1000};

    int actual = solution.rob(nums);
    int expected = 1000;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase5) {
    vector<int> nums = {200, 3, 140, 20, 10};

    int actual = solution.rob(nums);
    int expected = 340;

    EXPECT_EQ(actual, expected);
}