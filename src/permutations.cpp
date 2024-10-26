#include <gtest/gtest.h>

using namespace std;

class Solution1 {
  public:
    vector<vector<int>> permute(vector<int> &nums) {
        vector<vector<int>> result;
        vector<int> subset;

        backtrack(nums, result, subset);

        return result;
    }

  private:
    void backtrack(const vector<int> &nums, vector<vector<int>> &result,
                   vector<int> &subset) {
        if (subset.size() > nums.size()) {
            return;
        }

        if (subset.size() == nums.size()) {
            result.push_back(subset);
        }

        for (const int &num : nums) {
            bool skip =
                any_of(subset.begin(), subset.end(),
                       [&](const int &element) { return num == element; });
            if (skip) {
                continue;
            }

            subset.push_back(num);
            backtrack(nums, result, subset);
            subset.pop_back();
        }
    }
};

class Solution1Test : public ::testing::Test {
  protected:
    Solution1 solution;
};

TEST_F(Solution1Test, TestCase1) {
    vector<int> nums = {1, 2, 3};

    vector<vector<int>> actual = solution.permute(nums);
    vector<vector<int>> expected = {{1, 2, 3}, {1, 3, 2}, {2, 1, 3},
                                    {2, 3, 1}, {3, 1, 2}, {3, 2, 1}};

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase2) {
    vector<int> nums = {0, 1};

    vector<vector<int>> actual = solution.permute(nums);
    vector<vector<int>> expected = {{0, 1}, {1, 0}};

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase3) {
    vector<int> nums = {1};

    vector<vector<int>> actual = solution.permute(nums);
    vector<vector<int>> expected = {{1}};

    EXPECT_EQ(actual, expected);
}