#include <gtest/gtest.h>

using namespace std;

class Solution1 {
  public:
    int countSubstrings(string s) {
        int n = s.length();
        vector<vector<bool>> dp(n, vector<bool>(n, false));
        for (int i = 0; i < n; i++) {
            dp[i][i] = true;
        }

        for (int len = 2; len <= n; len++) {
            for (int i = 0; i <= n - len; i++) {
                int j = len + i - 1;

                if (len == 2) {
                    dp[i][j] = s[i] == s[j];
                } else {
                    dp[i][j] = s[i] == s[j] && dp[i + 1][j - 1];
                }
            }
        }

        int count = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                count += static_cast<int>(dp[i][j]);
            }
        }

        return count;
    }
};

class Solution1Test : public ::testing::Test {
  protected:
    Solution1 solution;
};

TEST_F(Solution1Test, TestCase1) {
    string s = "abc";

    int actual = solution.countSubstrings(s);
    int expected = 3;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase2) {
    string s = "aaa";

    int actual = solution.countSubstrings(s);
    int expected = 6;

    EXPECT_EQ(actual, expected);
}