#include <gtest/gtest.h>
#include <stdexcept>
#include <vector>

using namespace std;

class Solution {
  public:
    vector<int> twoSum(vector<int> &nums, int target) {
        for (int i = 0; i < nums.size(); i++) {
            for (int j = i + 1; j < nums.size(); j++) {
                if (nums.at(i) + nums.at(j) == target) {
                    return {i, j};
                }
            }
        }

        throw std::runtime_error("Unreachable");
    }
};

TEST(Solution, TwoSum1) {
    Solution solution;
    vector<int> expected{0, 1};
    vector<int> nums{2, 7, 11, 15};
    int target = 9;
    vector<int> actual = solution.twoSum(nums, target);
    EXPECT_EQ(expected, actual);
}

TEST(Solution, TwoSum2) {
    Solution solution;
    vector<int> expected{1, 2};
    vector<int> nums{3, 2, 4};
    int target = 6;
    vector<int> actual = solution.twoSum(nums, target);
    EXPECT_EQ(expected, actual);
}

TEST(Solution, TwoSum3) {
    Solution solution;
    vector<int> expected{0, 1};
    vector<int> nums{3, 3};
    int target = 6;
    vector<int> actual = solution.twoSum(nums, target);
    EXPECT_EQ(expected, actual);
}
