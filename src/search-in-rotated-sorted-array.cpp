#include <gtest/gtest.h>
#include <gtest/internal/gtest-internal.h>

using namespace std;

class Solution1 {
  public:
    int search(const vector<int> &nums, int target) {
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

        int pivot = left;

        left = 0;
        right = nums.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            int pivotedMid = (mid + pivot) % nums.size();
            if (nums[pivotedMid] == target) {
                return pivotedMid;
            } else if (nums[pivotedMid] < target) {
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

TEST_F(Solution1Test, TestCase1) {
    vector<int> nums = {4, 5, 6, 7, 0, 1, 2};
    int target = 0;

    int actual = solution.search(nums, target);
    int expected = 4;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase2) {
    vector<int> nums = {4, 5, 6, 7, 0, 1, 2};
    int target = 3;

    int actual = solution.search(nums, target);
    int expected = -1;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase3) {
    vector<int> nums = {1};
    int target = 0;

    int actual = solution.search(nums, target);
    int expected = -1;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase4) {
    vector<int> nums = {3, 1};
    int target = 1;

    int actual = solution.search(nums, target);
    int expected = 1;

    EXPECT_EQ(actual, expected);
}