#include <gtest/gtest.h>
#include <string>
#include <string_view>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution1 {
  public:
    bool wordBreak(string s, vector<string> &wordDict) {
        unordered_set<string_view> dict;
        for (const string &word : wordDict) {
            dict.insert(word);
        }

        int n = s.length();
        vector<bool> dp(n + 1, false);
        dp[0] = true;

        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < i; j++) {
                string_view substring(s.begin() + j, s.begin() + i);
                if (dp[j] && dict.contains(substring)) {
                    dp[i] = true;
                    break;
                }
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
    string s = "leetcode";
    vector<string> wordDict = {"leet", "code"};

    bool actual = solution.wordBreak(s, wordDict);
    bool expected = true;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase2) {
    string s = "applepenapple";
    vector<string> wordDict = {"apple", "pen"};

    bool actual = solution.wordBreak(s, wordDict);
    bool expected = true;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase3) {
    string s = "catsandog";
    vector<string> wordDict = {"cats", "dog", "sand", "and", "cat"};

    bool actual = solution.wordBreak(s, wordDict);
    bool expected = false;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase4) {
    string s = "aaaaaaa";
    vector<string> wordDict = {"aaaa", "aaa"};

    bool actual = solution.wordBreak(s, wordDict);
    bool expected = true;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase5) {
    string s = "dogs";
    vector<string> wordDict = {"dog", "s", "gs"};

    bool actual = solution.wordBreak(s, wordDict);
    bool expected = true;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase6) {
    string s = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
               "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
               "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
               "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
               "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab";
    vector<string> wordDict = {"a",
                               "aa",
                               "aaa",
                               "aaaa",
                               "aaaaa",
                               "aaaaaa",
                               "aaaaaaa",
                               "aaaaaaaa",
                               "aaaaaaaaa",
                               "aaaaaaaaaa",
                               "aaaaaaaaaaa",
                               "aaaaaaaaaaaa",
                               "aaaaaaaaaaaaa",
                               "aaaaaaaaaaaaaa",
                               "aaaaaaaaaaaaaaa",
                               "aaaaaaaaaaaaaaaa",
                               "aaaaaaaaaaaaaaaaa",
                               "aaaaaaaaaaaaaaaaaa",
                               "aaaaaaaaaaaaaaaaaaa",
                               "aaaaaaaaaaaaaaaaaaaa"};

    bool actual = solution.wordBreak(s, wordDict);
    bool expected = false;

    EXPECT_EQ(actual, expected);
}