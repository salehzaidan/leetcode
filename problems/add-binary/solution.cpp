#include <algorithm>
#include <gtest/gtest.h>
#include <string>

using namespace std;

class Solution {
  public:
    string addBinary(string a, string b) {
        auto smin = a;
        auto smax = b;
        if (smin.size() > smax.size()) {
            auto tmp = smin;
            smin = smax;
            smax = tmp;
        }

        string ans;
        int carry = 0;

        for (int i = smax.size() - 1; i >= 0; i--) {
            int m = 0;
            if (i < smax.size()) {
                m = stoul(string{smax.at(i)}, nullptr, 2);
            }

            int n = 0;
            auto j = i - (smax.size() - smin.size());
            if (j < smin.size()) {
                n = stoul(string{smin.at(j)}, nullptr, 2);
            }

            auto val = m + n + carry;
            carry = val / 2;
            ans += to_string(val % 2);
        }

        if (carry > 0) {
            ans.push_back('1');
        }

        reverse(ans.begin(), ans.end());
        return ans;
    }
};

TEST(Solution, AddBinary1) {
    Solution solution;
    string a{"11"};
    string b{"1"};
    string expected{"100"};
    string actual = solution.addBinary(a, b);
    EXPECT_EQ(expected, actual);
}

TEST(Solution, AddBinary2) {
    Solution solution;
    string a{"1010"};
    string b{"1011"};
    string expected{"10101"};
    string actual = solution.addBinary(a, b);
    EXPECT_EQ(expected, actual);
}

TEST(Solution, AddBinary3) {
    Solution solution;
    string a{"1"};
    string b{"1"};
    string expected{"10"};
    string actual = solution.addBinary(a, b);
    EXPECT_EQ(expected, actual);
}
