#include <gtest/gtest.h>

using namespace std;

class Solution1 {
  public:
    int findDuplicate(const vector<int> &nums) {
        int slow = nums[0];
        int fast = nums[nums[0]];

        while (slow != fast) {
            slow = nums[slow];
            fast = nums[nums[fast]];
        }

        slow = 0;
        while (slow != fast) {
            slow = nums[slow];
            fast = nums[fast];
        }

        return slow;
    }
};

class Solution1Test : public ::testing::Test {
  protected:
    Solution1 solution;
};

TEST_F(Solution1Test, TestCase1) {
    vector<int> nums = {1, 3, 4, 2, 2};

    int actual = solution.findDuplicate(nums);
    int expected = 2;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase2) {
    vector<int> nums = {3, 1, 3, 4, 2};

    int actual = solution.findDuplicate(nums);
    int expected = 3;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase3) {
    vector<int> nums = {3, 3, 3, 3, 3};

    int actual = solution.findDuplicate(nums);
    int expected = 3;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase4) {
    vector<int> nums = {2, 5, 9, 6, 9, 3, 8, 9, 7, 1};

    int actual = solution.findDuplicate(nums);
    int expected = 9;

    EXPECT_EQ(actual, expected);
}