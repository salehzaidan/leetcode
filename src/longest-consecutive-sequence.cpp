#include <algorithm>
#include <gtest/gtest.h>
#include <vector>

using namespace std;

class Solution1 {
public:
  int longestConsecutive(const vector<int> &nums) {
    if (nums.empty()) {
      return 0;
    }

    vector<int> copy(nums);
    sort(copy.begin(), copy.end());

    int current = 1;
    int longest = 1;
    for (int i = 1; i < copy.size(); i++) {
      int diff = copy[i] - copy[i - 1];
      if (diff == 0) {
        continue;
      } else if (diff == 1) {
        current++;
      } else {
        current = 1;
      }
      longest = max(longest, current);
    }

    return longest;
  }
};

TEST(Solution1, testCase1) {
  vector<int> nums = {100, 4, 200, 1, 3, 2};

  Solution1 solution;
  EXPECT_EQ(solution.longestConsecutive(nums), 4);
}

TEST(Solution1, testCase2) {
  vector<int> nums = {0, 3, 7, 2, 5, 8, 4, 6, 0, 1};

  Solution1 solution;
  EXPECT_EQ(solution.longestConsecutive(nums), 9);
}

TEST(Solution1, testCase3) {
  vector<int> nums;

  Solution1 solution;
  EXPECT_EQ(solution.longestConsecutive(nums), 0);
}

TEST(Solution1, testCase4) {
  vector<int> nums = {1, 2, 0, 1};

  Solution1 solution;
  EXPECT_EQ(solution.longestConsecutive(nums), 3);
}