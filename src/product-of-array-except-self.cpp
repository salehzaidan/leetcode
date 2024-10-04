#include <gtest/gtest.h>
#include <vector>

using namespace std;

class Solution1 {
public:
  vector<int> productExceptSelf(const vector<int> &nums) {
    vector<int> prefix(nums);
    for (int i = 1; i < nums.size(); i++) {
      prefix[i] = nums[i] * prefix[i - 1];
    }

    vector<int> suffix(nums);
    for (int i = nums.size() - 2; i >= 0; i--) {
      suffix[i] = nums[i] * suffix[i + 1];
    }

    vector<int> product(nums.size());
    for (int i = 0; i < nums.size(); i++) {
      int before = 1;
      if (i != 0) {
        before = prefix[i - 1];
      }

      int after = 1;
      if (i != nums.size() - 1) {
        after = suffix[i + 1];
      }

      product[i] = before * after;
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