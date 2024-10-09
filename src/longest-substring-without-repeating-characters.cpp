#include <gtest/gtest.h>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solution1 {
public:
  int lengthOfLongestSubstring(string s) {
    unordered_map<char, int> chars;
    int left = 0;
    int right = 0;
    int longest = 0;

    while (right < s.length()) {
      if (chars.count(s[right]) == 0) {
        chars[s[right]] = right;
      } else {
        left = chars[s[right]] + 1;
        chars.clear();
        for (int i = left; i <= right; i++) {
          chars[s[i]] = i;
        }
      }

      longest = max(longest, (int)chars.size());
      right++;
    }

    return longest;
  }
};

class Solution1Test : public ::testing::Test {
protected:
  Solution1 solution;
};

TEST_F(Solution1Test, TestCase1) {
  string s = "abcabcbb";

  int actual = solution.lengthOfLongestSubstring(s);
  int expected = 3;

  EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase2) {
  string s = "bbbbb";

  int actual = solution.lengthOfLongestSubstring(s);
  int expected = 1;

  EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase3) {
  string s = "pwwkew";

  int actual = solution.lengthOfLongestSubstring(s);
  int expected = 3;

  EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase4) {
  string s = "";

  int actual = solution.lengthOfLongestSubstring(s);
  int expected = 0;

  EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase5) {
  string s = "dvdf";

  int actual = solution.lengthOfLongestSubstring(s);
  int expected = 3;

  EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase6) {
  string s = "fioiwfqp";

  int actual = solution.lengthOfLongestSubstring(s);
  int expected = 6;

  EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase7) {
  string s = "iaoioiwgrrp";

  int actual = solution.lengthOfLongestSubstring(s);
  int expected = 5;

  EXPECT_EQ(actual, expected);
}

class Solution2 {
public:
  int lengthOfLongestSubstring(string s) {
    unordered_set<char> chars;
    int left = 0;
    int right = 0;
    int longest = 0;

    while (right < s.length()) {
      if (chars.count(s[right]) == 0) {
        chars.insert(s[right]);
        longest = max(longest, right - left + 1);
      } else {
        while (chars.count(s[right]) == 1) {
          chars.erase(s[left]);
          left++;
        }
        chars.insert(s[right]);
      }

      right++;
    }

    return longest;
  }
};

class Solution2Test : public ::testing::Test {
protected:
  Solution2 solution;
};

TEST_F(Solution2Test, TestCase1) {
  string s = "abcabcbb";

  int actual = solution.lengthOfLongestSubstring(s);
  int expected = 3;

  EXPECT_EQ(actual, expected);
}

TEST_F(Solution2Test, TestCase2) {
  string s = "bbbbb";

  int actual = solution.lengthOfLongestSubstring(s);
  int expected = 1;

  EXPECT_EQ(actual, expected);
}

TEST_F(Solution2Test, TestCase3) {
  string s = "pwwkew";

  int actual = solution.lengthOfLongestSubstring(s);
  int expected = 3;

  EXPECT_EQ(actual, expected);
}

TEST_F(Solution2Test, TestCase4) {
  string s = "";

  int actual = solution.lengthOfLongestSubstring(s);
  int expected = 0;

  EXPECT_EQ(actual, expected);
}

TEST_F(Solution2Test, TestCase5) {
  string s = "dvdf";

  int actual = solution.lengthOfLongestSubstring(s);
  int expected = 3;

  EXPECT_EQ(actual, expected);
}

TEST_F(Solution2Test, TestCase6) {
  string s = "fioiwfqp";

  int actual = solution.lengthOfLongestSubstring(s);
  int expected = 6;

  EXPECT_EQ(actual, expected);
}

TEST_F(Solution2Test, TestCase7) {
  string s = "iaoioiwgrrp";

  int actual = solution.lengthOfLongestSubstring(s);
  int expected = 5;

  EXPECT_EQ(actual, expected);
}