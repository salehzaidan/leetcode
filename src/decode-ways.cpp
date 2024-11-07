#include <gtest/gtest.h>
#include <vector>

using namespace std;

class Solution1 {
  public:
    int numDecodings(string s) {
        if (s[0] == '0') {
            return 0;
        }

        int n = s.length();
        vector<int> dp(n + 1, 0);
        dp[0] = 1;
        dp[1] = 1;

        for (int i = 2; i <= n; i++) {
            int num = s[i - 1] - '0';
            if (num > 0) {
                dp[i] += dp[i - 1];
            }

            num += (s[i - 2] - '0') * 10;
            if (num >= 10 && num <= 26) {
                dp[i] += dp[i - 2];
            }
        }

        return dp[n];
    }
};

class Solution1Test : public ::testing::Test {
  protected:
    Solution1 solution;
};

TEST_F(Solution1Test, TestCase1) {
    string s = "12";

    int actual = solution.numDecodings(s);
    int expected = 2;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase2) {
    string s = "226";

    int actual = solution.numDecodings(s);
    int expected = 3;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase3) {
    string s = "06";

    int actual = solution.numDecodings(s);
    int expected = 0;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase4) {
    string s = "10";

    int actual = solution.numDecodings(s);
    int expected = 1;

    EXPECT_EQ(actual, expected);
}