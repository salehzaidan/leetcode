#include <gtest/gtest.h>
#include <string>
#include <unordered_map>

using namespace std;

class Solution1 {
public:
  bool isAnagram(const string s, const string t) {
    if (s.length() != t.length()) {
      return false;
    }

    unordered_map<char, int> freq;

    for (const char &c : s) {
      freq[c]++;
    }

    for (const char &c : t) {
      freq[c]--;
    }

    for (const auto &entry : freq) {
      int count = entry.second;
      if (count != 0) {
        return false;
      }
    }

    return true;
  }
};

TEST(Solution1, testCase1) {
  string s = "anagram";
  string t = "nagaram";

  Solution1 solution;
  EXPECT_EQ(solution.isAnagram(s, t), true);
}

TEST(Solution1, testCase2) {
  string s = "rat";
  string t = "car";

  Solution1 solution;
  EXPECT_EQ(solution.isAnagram(s, t), false);
}

class Solution2 {
public:
  bool isAnagram(const string s, const string t) {
    if (s.length() != t.length()) {
      return false;
    }

    const int LETTERS_SIZE = 26;
    vector<int> freq(LETTERS_SIZE);

    for (int i = 0; i < s.length(); i++) {
      freq[s[i] - 'a']++;
      freq[t[i] - 'a']--;
    }

    for (const int &count : freq) {
      if (count != 0) {
        return false;
      }
    }

    return true;
  }
};

TEST(Solution2, testCase1) {
  string s = "anagram";
  string t = "nagaram";

  Solution2 solution;
  EXPECT_EQ(solution.isAnagram(s, t), true);
}

TEST(Solution2, testCase2) {
  string s = "rat";
  string t = "car";

  Solution2 solution;
  EXPECT_EQ(solution.isAnagram(s, t), false);
}