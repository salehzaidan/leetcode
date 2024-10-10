#include <gtest/gtest.h>
#include <stdexcept>
#include <vector>

using namespace std;

class Solution1 {
  public:
    vector<int> twoSum(const vector<int> &numbers, int target) {
        int left = 0;
        int right = numbers.size() - 1;
        while (left < right) {
            int sum = numbers[left] + numbers[right];

            if (sum < target) {
                left++;
                continue;
            }

            if (sum > target) {
                right--;
                continue;
            }

            if (sum == target) {
                return vector<int>{left + 1, right + 1};
            }
        }

        throw runtime_error("Unreachable");
    }
};

TEST(Solution1, testCase1) {
    vector<int> nums = {2, 7, 11, 15};
    int target = 9;

    vector<int> expected = {1, 2};

    Solution1 solution;
    EXPECT_EQ(solution.twoSum(nums, target), expected);
}

TEST(Solution1, testCase2) {
    vector<int> nums = {2, 3, 4};
    int target = 6;

    vector<int> expected = {1, 3};

    Solution1 solution;
    EXPECT_EQ(solution.twoSum(nums, target), expected);
}

TEST(Solution1, testCase3) {
    vector<int> nums = {-1, 0};
    int target = -1;

    vector<int> expected = {1, 2};

    Solution1 solution;
    EXPECT_EQ(solution.twoSum(nums, target), expected);
}