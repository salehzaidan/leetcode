#include <gtest/gtest.h>
#include <string>
#include <unordered_map>

using namespace std;

class Solution1 {
public:
  int characterReplacement(string s, int k) {
    unordered_map<char, int> freq;
    char frequentChar = '\0';
    int frequentLen = 0;
    int longestLen = 0;

    int left = 0;
    int right = 0;
    while (right < s.length()) {
      freq[s[right]]++;
      if (freq[s[right]] > frequentLen) {
        frequentLen = freq[s[right]];
        frequentChar = s[right];
      }

      if (right - left + 1 - frequentLen <= k) {
        longestLen = max(longestLen, right - left + 1);
      } else {
        freq[s[left]]--;
        if (s[left] == frequentChar) {
          frequentLen--;
        }
        left++;
      }
      right++;
    }

    return longestLen;
  }
};

class Solution1Test : public ::testing::Test {
protected:
  Solution1 solution;
};

TEST_F(Solution1Test, TestCase1) {
  string s = "ABAB";
  int k = 2;

  int actual = solution.characterReplacement(s, k);
  int expected = 4;

  EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase2) {
  string s = "AABABBA";
  int k = 1;

  int actual = solution.characterReplacement(s, k);
  int expected = 4;

  EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase3) {
  string s = "ABBB";
  int k = 2;

  int actual = solution.characterReplacement(s, k);
  int expected = 4;

  EXPECT_EQ(actual, expected);
}