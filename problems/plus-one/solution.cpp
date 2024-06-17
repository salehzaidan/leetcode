#include <algorithm>
#include <gtest/gtest.h>

using namespace std;

class Solution {
  public:
    vector<int> plusOne(vector<int> &digits) {
        vector<int> ans;
        int carry = 1;

        for (auto it = digits.rbegin(); it != digits.rend(); it++) {
            auto n = *it;

            n += carry;
            carry = n / 10;
            ans.push_back(n % 10);
        }

        if (carry > 0) {
            ans.push_back(carry);
        }

        reverse(ans.begin(), ans.end());
        return ans;
    }
};

TEST(Solution, PlusOne1) {
    Solution solution;
    vector<int> digits{1, 2, 3};
    vector<int> expected{1, 2, 4};
    vector<int> actual = solution.plusOne(digits);
    EXPECT_EQ(expected, actual);
}

TEST(Solution, PlusOne2) {
    Solution solution;
    vector<int> digits{4, 3, 2, 1};
    vector<int> expected{4, 3, 2, 2};
    vector<int> actual = solution.plusOne(digits);
    EXPECT_EQ(expected, actual);
}

TEST(Solution, PlusOne3) {
    Solution solution;
    vector<int> digits{9};
    vector<int> expected{1, 0};
    vector<int> actual = solution.plusOne(digits);
    EXPECT_EQ(expected, actual);
}
