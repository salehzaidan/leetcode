#include <algorithm>
#include <gtest/gtest.h>
#include <numeric>

using namespace std;

class Solution1 {
  public:
    vector<vector<int>> combinationSum2(const vector<int> &candidates,
                                        int target) {
        vector<vector<int>> result;
        vector<int> combination;

        vector<int> copy = candidates;
        sort(copy.begin(), copy.end());

        backtrack(copy, target, result, combination, 0);

        return result;
    }

  private:
    void backtrack(const vector<int> &candidates, int target,
                   vector<vector<int>> &result, vector<int> &combination,
                   int index) {
        int sum = accumulate(combination.begin(), combination.end(), 0);

        if (sum > target) {
            return;
        }

        if (sum == target) {
            result.push_back(combination);
            return;
        }

        for (int i = index; i < candidates.size(); i++) {
            if (i > index && candidates[i] == candidates[i - 1]) {
                continue;
            }

            combination.push_back(candidates[i]);
            backtrack(candidates, target, result, combination, i + 1);
            combination.pop_back();
        }
    }
};

class Solution1Test : public ::testing::Test {
  protected:
    Solution1 solution;
};

TEST_F(Solution1Test, TestCase1) {
    vector<int> candidates = {10, 1, 2, 7, 6, 1, 5};
    int target = 8;

    vector<vector<int>> actual = solution.combinationSum2(candidates, target);
    vector<vector<int>> expected = {{1, 1, 6}, {1, 2, 5}, {1, 7}, {2, 6}};

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase2) {
    vector<int> candidates = {2, 5, 2, 1, 2};
    int target = 5;

    vector<vector<int>> actual = solution.combinationSum2(candidates, target);
    vector<vector<int>> expected = {{1, 2, 2}, {5}};

    EXPECT_EQ(actual, expected);
}