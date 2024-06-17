#include <gtest/gtest.h>

using namespace std;

class Solution {
  public:
    int searchInsert(vector<int> &nums, int target) {
        size_t i = 0;
        size_t j = nums.size() - 1;

        while (i <= j) {
            auto k = i + (j - i) / 2;
            auto mid = nums.at(k);

            if (mid == target) {
                return k;
            }

            if (mid > target) {
                if (k == 0) {
                    return 0;
                }

                j = k - 1;
            } else {
                i = k + 1;
            }
        }

        return i;
    }
};

TEST(Solution, SearchInsert1) {
    Solution solution;
    vector<int> nums{1, 3, 5, 6};
    int target = 5;
    int expected = 2;
    int actual = solution.searchInsert(nums, target);
    EXPECT_EQ(expected, actual);
}

TEST(Solution, SearchInsert2) {
    Solution solution;
    vector<int> nums{1, 3, 5, 6};
    int target = 2;
    int expected = 1;
    int actual = solution.searchInsert(nums, target);
    EXPECT_EQ(expected, actual);
}

TEST(Solution, SearchInsert3) {
    Solution solution;
    vector<int> nums{1, 3, 5, 6};
    int target = 7;
    int expected = 4;
    int actual = solution.searchInsert(nums, target);
    EXPECT_EQ(expected, actual);
}

TEST(Solution, SearchInsert4) {
    Solution solution;
    vector<int> nums{1, 3, 5, 6};
    int target = 0;
    int expected = 0;
    int actual = solution.searchInsert(nums, target);
    EXPECT_EQ(expected, actual);
}

TEST(Solution, SearchInsert5) {
    Solution solution;
    vector<int> nums{1};
    int target = 2;
    int expected = 1;
    int actual = solution.searchInsert(nums, target);
    EXPECT_EQ(expected, actual);
}
