#include <algorithm>
#include <gtest/gtest.h>
#include <numeric>

using namespace std;

class Solution1 {
  public:
    vector<vector<int>> combinationSum(vector<int> &candidates, int target) {
        vector<vector<int>> result;
        vector<int> combination;

        backtrack(candidates, target, result, combination);

        return result;
    }

  private:
    void backtrack(const vector<int> &candidates, int target,
                   vector<vector<int>> &result, vector<int> &combination) {
        int sum = accumulate(combination.begin(), combination.end(), 0);

        if (sum > target) {
            return;
        }

        if (sum == target) {
            result.push_back(combination);
            return;
        }

        for (const int &candidate : candidates) {
            bool skip =
                any_of(combination.begin(), combination.end(),
                       [&](const int &element) { return candidate < element; });
            if (skip) {
                continue;
            }

            combination.push_back(candidate);
            backtrack(candidates, target, result, combination);
            combination.pop_back();
        }
    }
};

class Solution1Test : public ::testing::Test {
  protected:
    Solution1 solution;
};

TEST_F(Solution1Test, TestCase1) {
    vector<int> candidates = {2, 3, 6, 7};
    int target = 7;

    vector<vector<int>> actual = solution.combinationSum(candidates, target);
    vector<vector<int>> expected = {{2, 2, 3}, {7}};

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase2) {
    vector<int> candidates = {2, 3, 5};
    int target = 8;

    vector<vector<int>> actual = solution.combinationSum(candidates, target);
    vector<vector<int>> expected = {{2, 2, 2, 2}, {2, 3, 3}, {3, 5}};

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase3) {
    vector<int> candidates = {2};
    int target = 1;

    vector<vector<int>> actual = solution.combinationSum(candidates, target);
    vector<vector<int>> expected = {};

    EXPECT_EQ(actual, expected);
}