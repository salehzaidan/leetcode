#include <gtest/gtest.h>
#include <unordered_map>

using namespace std;

class Solution1 {
public:
  bool checkInclusion(string s1, string s2) {
    int k = s1.size();
    if (k > s2.size()) {
      return false;
    }

    unordered_map<char, int> freq1;
    for (const char &c : s1) {
      freq1[c]++;
    }

    unordered_map<char, int> freq2;
    for (int i = 0; i < k; i++) {
      freq2[s2[i]]++;
    }

    for (int i = k; i <= s2.size(); i++) {
      bool ok = true;
      for (const auto &p : freq1) {
        char ch = p.first;
        int count = p.second;
        if (freq2[ch] != count) {
          ok = false;
          break;
        }
      }

      if (ok) {
        return true;
      }

      freq2[s2[i - k]]--;
      freq2[s2[i]]++;
    }

    return false;
  }
};

class Solution1Test : public ::testing::Test {
protected:
  Solution1 solution;
};

TEST_F(Solution1Test, TestCase1) {
  string s1 = "ab";
  string s2 = "eidbaooo";

  bool actual = solution.checkInclusion(s1, s2);
  bool expected = true;

  EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase2) {
  string s1 = "ab";
  string s2 = "eidboaoo";

  bool actual = solution.checkInclusion(s1, s2);
  bool expected = false;

  EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase3) {
  string s1 = "ab";
  string s2 = "eidoooab";

  bool actual = solution.checkInclusion(s1, s2);
  bool expected = true;

  EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase4) {
  string s1 = "dinitrophenylhydrazine";
  string s2 = "dimethylhydrazine";

  bool actual = solution.checkInclusion(s1, s2);
  bool expected = false;

  EXPECT_EQ(actual, expected);
}