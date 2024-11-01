#include <gtest/gtest.h>
#include <queue>
#include <vector>

using namespace std;

class Solution1 {
  public:
    int findKthLargest(vector<int> &nums, int k) {
        priority_queue<int> q(nums.begin(), nums.end());
        while (q.size() > nums.size() - k + 1) {
            q.pop();
        }
        return q.top();
    }
};

class Solution1Test : public ::testing::Test {
  protected:
    Solution1 solution;
};

TEST_F(Solution1Test, TestCase1) {
    vector<int> nums = {3, 2, 1, 5, 6, 4};
    int k = 2;

    int actual = solution.findKthLargest(nums, k);
    int expected = 5;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase2) {
    vector<int> nums = {3, 2, 3, 1, 2, 4, 5, 5, 6};
    int k = 4;

    int actual = solution.findKthLargest(nums, k);
    int expected = 4;

    EXPECT_EQ(actual, expected);
}