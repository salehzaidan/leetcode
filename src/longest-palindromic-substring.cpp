#include <gtest/gtest.h>
#include <string>
#include <vector>

using namespace std;

class Solution1 {
  public:
    string longestPalindrome(const string &s) {
        int n = s.length();
        vector<vector<bool>> dp(n, vector<bool>(n, false));
        for (int i = 0; i < n; i++) {
            dp[i][i] = true;
        }

        int start = 0;
        int maxLength = 1;

        for (int len = 2; len <= n; len++) {
            for (int i = 0; i <= n - len; i++) {
                int j = len + i - 1;

                if (len == 2) {
                    dp[i][j] = s[i] == s[j];
                } else {
                    dp[i][j] = s[i] == s[j] && dp[i + 1][j - 1];
                }

                if (dp[i][j] && len > maxLength) {
                    start = i;
                    maxLength = len;
                }
            }
        }

        return s.substr(start, maxLength);
    }
};

class Solution1Test : public ::testing::Test {
  protected:
    Solution1 solution;
};

TEST_F(Solution1Test, TestCase1) {
    string s = "babad";

    string actual = solution.longestPalindrome(s);
    string expected = "bab";

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase2) {
    string s = "cbbd";

    string actual = solution.longestPalindrome(s);
    string expected = "bb";

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase3) {
    string s = "a";

    string actual = solution.longestPalindrome(s);
    string expected = "a";

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase4) {
    string s = "aa";

    string actual = solution.longestPalindrome(s);
    string expected = "aa";

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase5) {
    string s = "ab";

    string actual = solution.longestPalindrome(s);
    string expected = "a";

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase6) {
    string s = "aaaa";

    string actual = solution.longestPalindrome(s);
    string expected = "aaaa";

    EXPECT_EQ(actual, expected);
}

class Solution2 {
  public:
    string longestPalindrome(const string &s) {
        int start = 0;
        int maxLength = 1;

        for (int i = 0; i < s.length(); i++) {
            auto odd = expandAroundCenter(s, i, i);
            if (odd.second > maxLength) {
                start = odd.first;
                maxLength = odd.second;
            }

            auto even = expandAroundCenter(s, i, i + 1);
            if (even.second > maxLength) {
                start = even.first;
                maxLength = even.second;
            }
        }

        return s.substr(start, maxLength);
    }

  private:
    pair<int, int> expandAroundCenter(const string &s, int left, int right) {
        int start = 0;
        int maxLength = 1;

        while (left >= 0 && right < s.length() && s[left] == s[right]) {
            int len = right - left + 1;
            if (len > maxLength) {
                start = left;
                maxLength = len;
            }
            left--;
            right++;
        }

        return {start, maxLength};
    }
};

class Solution2Test : public ::testing::Test {
  protected:
    Solution2 solution;
};

TEST_F(Solution2Test, TestCase1) {
    string s = "babad";

    string actual = solution.longestPalindrome(s);
    string expected = "bab";

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution2Test, TestCase2) {
    string s = "cbbd";

    string actual = solution.longestPalindrome(s);
    string expected = "bb";

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution2Test, TestCase3) {
    string s = "a";

    string actual = solution.longestPalindrome(s);
    string expected = "a";

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution2Test, TestCase4) {
    string s = "aa";

    string actual = solution.longestPalindrome(s);
    string expected = "aa";

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution2Test, TestCase5) {
    string s = "ab";

    string actual = solution.longestPalindrome(s);
    string expected = "a";

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution2Test, TestCase6) {
    string s = "aaaa";

    string actual = solution.longestPalindrome(s);
    string expected = "aaaa";

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution2Test, TestCase7) {
    string s = "aacabdkacaa";

    string actual = solution.longestPalindrome(s);
    string expected = "aca";

    EXPECT_EQ(actual, expected);
}