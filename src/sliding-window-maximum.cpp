#include <deque>
#include <gtest/gtest.h>

using namespace std;

class Solution1 {
  public:
    vector<int> maxSlidingWindow(const vector<int> &nums, int k) {
        vector<int> maxWindows;
        deque<int> indices;

        for (int i = 0; i < nums.size(); i++) {
            if (!indices.empty() && indices.front() < i - k + 1) {
                indices.pop_front();
            }
            while (!indices.empty() && nums[i] > nums[indices.back()]) {
                indices.pop_back();
            }
            indices.push_back(i);

            if (i >= k - 1) {
                maxWindows.push_back(nums[indices.front()]);
            }
        }

        return maxWindows;
    }
};

class Solution1Test : public ::testing::Test {
  protected:
    Solution1 solution;
};

TEST_F(Solution1Test, TestCase1) {
    vector<int> nums = {1, 3, -1, -3, 5, 3, 6, 7};
    int k = 3;

    vector<int> actual = solution.maxSlidingWindow(nums, k);
    vector<int> expected = {3, 3, 5, 5, 6, 7};

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase2) {
    // GTEST_SKIP();
    vector<int> nums = {1};
    int k = 1;

    vector<int> actual = solution.maxSlidingWindow(nums, k);
    vector<int> expected = {1};

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase3) {
    // GTEST_SKIP();
    vector<int> nums = {1, 3, -1, -3, 5, 3, 6, 7};
    int k = 2;

    vector<int> actual = solution.maxSlidingWindow(nums, k);
    vector<int> expected = {3, 3, -1, 5, 5, 6, 7};

    EXPECT_EQ(actual, expected);
}