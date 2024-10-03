#include <algorithm>
#include <functional>
#include <gtest/gtest.h>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution1 {
public:
  vector<int> topKFrequent(const vector<int> &nums, int k) {
    unordered_map<int, int> countMap;
    for (const int &num : nums) {
      countMap[num]++;
    }

    vector<pair<int, int>> countVec(countMap.begin(), countMap.end());
    sort(
        countVec.begin(), countVec.end(),
        [](pair<int, int> a, pair<int, int> b) { return a.second > b.second; });

    vector<int> result;
    for (int i = 0; i < k; i++) {
      result.push_back(countVec[i].first);
    }

    return result;
  }
};

TEST(Solution1, testCase1) {
  vector<int> nums = {1, 1, 1, 2, 2, 3};
  int k = 2;

  vector<int> expected = {1, 2};

  Solution1 solution;
  EXPECT_EQ(solution.topKFrequent(nums, k), expected);
}

TEST(Solution1, testCase2) {
  vector<int> nums = {1};
  int k = 1;

  vector<int> expected = {1};

  Solution1 solution;
  EXPECT_EQ(solution.topKFrequent(nums, k), expected);
}

TEST(Solution1, testCase3) {
  vector<int> nums = {3, 0, 1, 0};
  int k = 1;

  vector<int> expected = {0};

  Solution1 solution;
  EXPECT_EQ(solution.topKFrequent(nums, k), expected);
}