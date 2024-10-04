#include <gtest/gtest.h>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution1 {
public:
  bool containsDuplicate(const vector<int> &nums) {
    unordered_map<int, int> freq;

    for (const int &num : nums) {
      int &count = freq[num];
      count++;

      if (count > 1) {
        return true;
      }
    }

    return false;
  }
};

TEST(Solution1, testCase1) {
  vector<int> nums = {1, 2, 3, 1};

  Solution1 solution;
  EXPECT_EQ(solution.containsDuplicate(nums), true);
}

TEST(Solution1, testCase2) {
  vector<int> nums = {1, 2, 3, 4};

  Solution1 solution;
  EXPECT_EQ(solution.containsDuplicate(nums), false);
}

TEST(Solution1, testCase3) {
  vector<int> nums = {1, 1, 1, 3, 3, 4, 3, 2, 4, 2};

  Solution1 solution;
  EXPECT_EQ(solution.containsDuplicate(nums), true);
}