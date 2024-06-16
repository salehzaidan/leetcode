#include <algorithm>
#include <gtest/gtest.h>

using namespace std;

class Solution {
  public:
    int removeElement(vector<int> &nums, int val) {
        size_t i = 0;
        size_t j = 0;

        while (i < nums.size() && j < nums.size()) {
            if (nums.at(i) != val) {
                i++;
                continue;
            }
            if (nums.at(j) == val || j < i) {
                j++;
                continue;
            }

            auto tmp = nums.at(i);
            nums.at(i) = nums.at(j);
            nums.at(j) = tmp;
            i++;
            j++;
        }

        return i;
    }
};

TEST(Solution, RemoveElement1) {
    Solution solution;
    vector<int> nums{3, 2, 2, 3};
    vector<int> expected{2, 2};
    int k = solution.removeElement(nums, 3);
    EXPECT_EQ(expected.size(), k);
    sort(nums.begin(), nums.begin() + k);
    for (size_t i = 0; i < k; i++) {
        EXPECT_EQ(nums.at(i), expected.at(i));
    }
}

TEST(Solution, RemoveElement2) {
    Solution solution;
    vector<int> nums{0, 1, 2, 2, 3, 0, 4, 2};
    vector<int> expected{0, 0, 1, 3, 4};
    int k = solution.removeElement(nums, 2);
    EXPECT_EQ(expected.size(), k);
    sort(nums.begin(), nums.begin() + k);
    for (size_t i = 0; i < k; i++) {
        EXPECT_EQ(nums.at(i), expected.at(i));
    }
}
