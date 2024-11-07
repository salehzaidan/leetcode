#include <gtest/gtest.h>
#include <vector>

using namespace std;

class Solution1 {
  public:
    int maxProduct(vector<int> &nums) {
        int n = nums.size();
        vector<int> maxProducts(n, 1);
        vector<int> minProducts(n, 1);

        maxProducts[0] = nums[0];
        minProducts[0] = nums[0];

        int result = nums[0];

        for (int i = 1; i < n; i++) {
            maxProducts[i] = max(maxProducts[i - 1] * nums[i],
                                 max(minProducts[i - 1] * nums[i], nums[i]));
            minProducts[i] = min(minProducts[i - 1] * nums[i],
                                 min(maxProducts[i - 1] * nums[i], nums[i]));

            result = max(result, maxProducts[i]);
        }

        return result;
    }
};

class Solution1Test : public ::testing::Test {
  protected:
    Solution1 solution;
};

TEST_F(Solution1Test, TestCase1) {
    vector<int> nums = {2, 3, -2, 4};

    int actual = solution.maxProduct(nums);
    int expected = 6;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase2) {
    vector<int> nums = {-2, 0, -1};

    int actual = solution.maxProduct(nums);
    int expected = 0;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase3) {
    vector<int> nums = {-10, 10, -10, 10};

    int actual = solution.maxProduct(nums);
    int expected = 10000;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase4) {
    vector<int> nums = {-2};

    int actual = solution.maxProduct(nums);
    int expected = -2;

    EXPECT_EQ(actual, expected);
}