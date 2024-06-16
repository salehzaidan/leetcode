#include <gtest/gtest.h>
#include <vector>

using namespace std;

class Solution {
  public:
    int removeDuplicates(vector<int> &nums) {
        size_t i = 1;

        for (size_t j = 1; j < nums.size(); j++) {
            if (nums.at(j) != nums.at(j - 1)) {
                nums.at(i) = nums.at(j);
                i++;
            }
        }

        return i;
    }
};

TEST(Solution, RemoveDuplicates1) {
    Solution solution;
    vector<int> nums{1, 1, 2};
    vector<int> expected{1, 2};
    int k = solution.removeDuplicates(nums);
    EXPECT_EQ(expected.size(), k);
    for (size_t i = 0; i < k; i++) {
        EXPECT_EQ(nums.at(i), expected.at(i));
    }
}

TEST(Solution, RemoveDuplicates2) {
    Solution solution;
    vector<int> nums{0, 0, 1, 1, 1, 2, 2, 3, 3, 4};
    vector<int> expected{0, 1, 2, 3, 4};
    int k = solution.removeDuplicates(nums);
    EXPECT_EQ(expected.size(), k);
    for (size_t i = 0; i < k; i++) {
        EXPECT_EQ(nums.at(i), expected.at(i));
    }
}
