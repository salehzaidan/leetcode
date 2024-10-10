#include <gtest/gtest.h>

using namespace std;

class Solution1 {
  public:
    int findMin(const vector<int> &nums) {
        int left = 0;
        int right = nums.size() - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] < nums[left]) {
                right = mid;
            } else if (nums[mid] > nums[right]) {
                left = mid + 1;
            } else {
                break;
            }
        }

        return nums[left];
    }
};

class Solution1Test : public ::testing::Test {
  protected:
    Solution1 solution;
};

TEST_F(Solution1Test, TestCase1) {
    vector<int> nums = {3, 4, 5, 1, 2};

    int actual = solution.findMin(nums);
    int expected = 1;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase2) {
    vector<int> nums = {4, 5, 6, 7, 0, 1, 2};

    int actual = solution.findMin(nums);
    int expected = 0;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase3) {
    vector<int> nums = {11, 13, 15, 17};

    int actual = solution.findMin(nums);
    int expected = 11;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase4) {
    vector<int> nums = {3, 1, 2};

    int actual = solution.findMin(nums);
    int expected = 1;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase5) {
    vector<int> nums = {1};

    int actual = solution.findMin(nums);
    int expected = 1;

    EXPECT_EQ(actual, expected);
}