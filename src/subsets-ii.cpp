#include <algorithm>
#include <gtest/gtest.h>
#include <vector>

using namespace std;

class Solution1 {
  public:
    vector<vector<int>> subsetsWithDup(const vector<int> &nums) {
        vector<vector<int>> result;
        vector<int> subset;

        vector<int> copy = nums;
        sort(copy.begin(), copy.end());
        backtrack(copy, result, subset, 0);

        return result;
    }

  private:
    void backtrack(const vector<int> &nums, vector<vector<int>> &result,
                   vector<int> &subset, int index) {
        result.push_back(subset);

        for (int i = index; i < nums.size(); i++) {
            if (i > index && nums[i] == nums[i - 1]) {
                continue;
            }

            subset.push_back(nums[i]);
            backtrack(nums, result, subset, i + 1);
            subset.pop_back();
        }
    }
};

class Solution1Test : public ::testing::Test {
  protected:
    Solution1 solution;
};

TEST_F(Solution1Test, TestCase1) {
    vector<int> nums = {1, 2, 2};

    vector<vector<int>> actual = solution.subsetsWithDup(nums);
    vector<vector<int>> expected = {{}, {1}, {1, 2}, {1, 2, 2}, {2}, {2, 2}};

    sort(actual.begin(), actual.end());
    sort(expected.begin(), expected.end());
    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase2) {
    vector<int> nums = {0};

    vector<vector<int>> actual = solution.subsetsWithDup(nums);
    vector<vector<int>> expected = {{}, {0}};

    sort(actual.begin(), actual.end());
    sort(expected.begin(), expected.end());
    EXPECT_EQ(actual, expected);
}