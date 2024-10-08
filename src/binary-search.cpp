#include <gtest/gtest.h>

using namespace std;

class Solution1 {
public:
  int search(vector<int> &nums, int target) {
    int left = 0;
    int right = nums.size() - 1;
    while (left <= right) {
      int mid = left + (right - left) / 2;
      if (nums[mid] == target) {
        return mid;
      } else if (nums[mid] < target) {
        left = mid + 1;
      } else {
        right = mid - 1;
      }
    }

    return -1;
  }
};

class Solution1Test : public ::testing::Test {
protected:
  Solution1 solution;
};

TEST_F(Solution1Test, testCase1) {
  vector<int> nums = {-1, 0, 3, 5, 9, 12};
  int target = 9;

  int actual = solution.search(nums, target);
  int expected = 4;

  EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, testCase2) {
  vector<int> nums = {-1, 0, 3, 5, 9, 12};
  int target = 2;

  int actual = solution.search(nums, target);
  int expected = -1;

  EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, testCase3) {
  vector<int> nums = {1, 2, 5, 7, 9};
  int target = 2;

  int actual = solution.search(nums, target);
  int expected = 1;

  EXPECT_EQ(actual, expected);
}