#include <algorithm>
#include <gtest/gtest.h>
#include <vector>

using namespace std;

class Solution1 {
  public:
    vector<vector<int>> subsets(vector<int> &nums) {
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

        result.push_back(subset);

        for (const int &num : nums) {
            bool skip =
                any_of(subset.begin(), subset.end(),
                       [&](const int &element) { return num <= element; });
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

    vector<vector<int>> actual = solution.subsets(nums);
    vector<vector<int>> expected = {{},  {1},    {2},    {1, 2},
                                    {3}, {1, 3}, {2, 3}, {1, 2, 3}};

    sort(actual.begin(), actual.end());
    sort(expected.begin(), expected.end());
    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase2) {
    vector<int> nums = {0};

    vector<vector<int>> actual = solution.subsets(nums);
    vector<vector<int>> expected = {{}, {0}};

    sort(actual.begin(), actual.end());
    sort(expected.begin(), expected.end());
    EXPECT_EQ(actual, expected);
}

class Solution2 {
  public:
    vector<vector<int>> subsets(vector<int> &nums) {
        vector<vector<int>> result;
        vector<int> subset;

        backtrack(nums, result, subset, 0);

        return result;
    }

  private:
    void backtrack(const vector<int> &nums, vector<vector<int>> &result,
                   vector<int> &subset, int index) {
        if (index == nums.size()) {
            result.push_back(subset);
            return;
        }

        subset.push_back(nums[index]);
        backtrack(nums, result, subset, index + 1);

        subset.pop_back();
        backtrack(nums, result, subset, index + 1);
    }
};

class Solution2Test : public ::testing::Test {
  protected:
    Solution2 solution;
};

TEST_F(Solution2Test, TestCase1) {
    vector<int> nums = {1, 2, 3};

    vector<vector<int>> actual = solution.subsets(nums);
    vector<vector<int>> expected = {{},  {1},    {2},    {1, 2},
                                    {3}, {1, 3}, {2, 3}, {1, 2, 3}};

    sort(actual.begin(), actual.end());
    sort(expected.begin(), expected.end());
    EXPECT_EQ(actual, expected);
}

TEST_F(Solution2Test, TestCase2) {
    vector<int> nums = {0};

    vector<vector<int>> actual = solution.subsets(nums);
    vector<vector<int>> expected = {{}, {0}};

    sort(actual.begin(), actual.end());
    sort(expected.begin(), expected.end());
    EXPECT_EQ(actual, expected);
}