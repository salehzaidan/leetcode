#include <gtest/gtest.h>
#include <string>
#include <unordered_map>

using namespace std;

class Solution1 {
public:
  bool isAnagram(const string s, const string t) {
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

TEST(isAnagram, testCase1) {
  string s = "anagram";
  string t = "nagaram";

  Solution1 solution;
  EXPECT_EQ(solution.isAnagram(s, t), true);
}

TEST(isAnagram, testCase2) {
  string s = "rat";
  string t = "car";

  Solution1 solution;
  EXPECT_EQ(solution.isAnagram(s, t), false);
}