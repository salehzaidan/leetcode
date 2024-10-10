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
                if (nums[i] + nums[j] == target) {
                    return vector<int>{i, j};
                }
            }
        }

        throw runtime_error("Unreachable");
    }
};

TEST(Solution1, testCase1) {
    vector<int> nums = {2, 7, 11, 15};
    int target = 9;
    vector<int> expected = {0, 1};

    Solution1 solution;
    EXPECT_EQ(solution.twoSum(nums, target), expected);
}

TEST(Solution1, testCase2) {
    vector<int> nums = {3, 2, 4};
    int target = 6;
    vector<int> expected = {1, 2};

    Solution1 solution;
    EXPECT_EQ(solution.twoSum(nums, target), expected);
}

TEST(Solution1, testCase3) {
    vector<int> nums = {3, 3};
    int target = 6;
    vector<int> expected = {0, 1};

    Solution1 solution;
    EXPECT_EQ(solution.twoSum(nums, target), expected);
}

class Solution2 {
  public:
    vector<int> twoSum(vector<int> &nums, int target) {
        unordered_map<int, int> indices;
        for (int i = 0; i < nums.size(); i++) {
            indices[nums[i]] = i;
        }

        for (int i = 0; i < nums.size(); i++) {
            int complement = target - nums[i];
            auto it = indices.find(complement);

            if (it == indices.end()) {
                continue;
            }

            int j = it->second;
            if (i != j) {
                return vector<int>{i, j};
            }
        }

        throw runtime_error("Unreachable");
    }
};

TEST(Solution2, testCase1) {
    vector<int> nums = {2, 7, 11, 15};
    int target = 9;
    vector<int> expected = {0, 1};

    Solution2 solution;
    EXPECT_EQ(solution.twoSum(nums, target), expected);
}

TEST(Solution2, testCase2) {
    vector<int> nums = {3, 2, 4};
    int target = 6;
    vector<int> expected = {1, 2};

    Solution2 solution;
    EXPECT_EQ(solution.twoSum(nums, target), expected);
}

TEST(Solution2, testCase3) {
    vector<int> nums = {3, 3};
    int target = 6;
    vector<int> expected = {0, 1};

    Solution2 solution;
    EXPECT_EQ(solution.twoSum(nums, target), expected);
}