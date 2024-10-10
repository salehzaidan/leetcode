#include <gtest/gtest.h>
#include <vector>

using namespace std;

class Solution1 {
  public:
    vector<int> productExceptSelf(const vector<int> &nums) {
        vector<int> prefix(nums.size());
        prefix[0] = 1;
        for (int i = 1; i < nums.size(); i++) {
            prefix[i] = prefix[i - 1] * nums[i - 1];
        }

        vector<int> suffix(nums.size());
        suffix[nums.size() - 1] = 1;
        for (int i = nums.size() - 2; i >= 0; i--) {
            suffix[i] = suffix[i + 1] * nums[i + 1];
        }

        vector<int> product(nums.size());
        for (int i = 0; i < nums.size(); i++) {
            product[i] = prefix[i] * suffix[i];
        }

        return product;
    }
};

TEST(Solution1, testCase1) {
    vector<int> nums = {1, 2, 3, 4};

    vector<int> expected = {24, 12, 8, 6};

    Solution1 solution;
    EXPECT_EQ(solution.productExceptSelf(nums), expected);
}

TEST(Solution1, testCase2) {
    vector<int> nums = {-1, 1, 0, -3, 3};

    vector<int> expected = {0, 0, 9, 0, 0};

    Solution1 solution;
    EXPECT_EQ(solution.productExceptSelf(nums), expected);
}

class Solution2 {
  public:
    vector<int> productExceptSelf(const vector<int> &nums) {
        vector<int> product(nums.size(), 1);

        int current = nums.front();
        for (int i = 1; i < nums.size(); i++) {
            product[i] *= current;
            current *= nums[i];
        }

        current = nums.back();
        for (int i = nums.size() - 2; i >= 0; i--) {
            product[i] *= current;
            current *= nums[i];
        }

        return product;
    }
};

TEST(Solution2, testCase1) {
    vector<int> nums = {1, 2, 3, 4};

    vector<int> expected = {24, 12, 8, 6};

    Solution2 solution;
    EXPECT_EQ(solution.productExceptSelf(nums), expected);
}

TEST(Solution2, testCase2) {
    vector<int> nums = {-1, 1, 0, -3, 3};

    vector<int> expected = {0, 0, 9, 0, 0};

    Solution2 solution;
    EXPECT_EQ(solution.productExceptSelf(nums), expected);
}