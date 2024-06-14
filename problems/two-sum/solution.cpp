#include <gtest/gtest.h>
#include <stdexcept>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution1 {
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

TEST(Solution1, TwoSum1) {
    Solution1 solution;
    vector<int> expected{0, 1};
    vector<int> nums{2, 7, 11, 15};
    int target = 9;
    vector<int> actual = solution.twoSum(nums, target);
    EXPECT_EQ(expected, actual);
}

TEST(Solution1, TwoSum2) {
    Solution1 solution;
    vector<int> expected{1, 2};
    vector<int> nums{3, 2, 4};
    int target = 6;
    vector<int> actual = solution.twoSum(nums, target);
    EXPECT_EQ(expected, actual);
}

TEST(Solution1, TwoSum3) {
    Solution1 solution;
    vector<int> expected{0, 1};
    vector<int> nums{3, 3};
    int target = 6;
    vector<int> actual = solution.twoSum(nums, target);
    EXPECT_EQ(expected, actual);
}

class Solution2 {
  public:
    vector<int> twoSum(vector<int> &nums, int target) {
        unordered_map<int, int> indices;

        for (int i = 0; i < nums.size(); i++) {
            auto a = nums.at(i);
            indices.insert({a, i});

            auto b = target - a;
            if (!indices.contains(b)) {
                continue;
            }

            auto j = indices.at(b);
            if (i < j) {
                return {i, j};
            }
            if (i > j) {
                return {j, i};
            }
        }

        throw std::runtime_error("Unreachable");
    }
};

TEST(Solution2, TwoSum1) {
    Solution2 solution;
    vector<int> expected{0, 1};
    vector<int> nums{2, 7, 11, 15};
    int target = 9;
    vector<int> actual = solution.twoSum(nums, target);
    EXPECT_EQ(expected, actual);
}

TEST(Solution2, TwoSum2) {
    Solution2 solution;
    vector<int> expected{1, 2};
    vector<int> nums{3, 2, 4};
    int target = 6;
    vector<int> actual = solution.twoSum(nums, target);
    EXPECT_EQ(expected, actual);
}

TEST(Solution2, TwoSum3) {
    Solution2 solution;
    vector<int> expected{0, 1};
    vector<int> nums{3, 3};
    int target = 6;
    vector<int> actual = solution.twoSum(nums, target);
    EXPECT_EQ(expected, actual);
}
