#include <algorithm>
#include <cctype>
#include <gtest/gtest.h>
#include <string>

using namespace std;

class Solution1 {
public:
  bool isPalindrome(string s) {
    transform(s.begin(), s.end(), s.begin(), [](char c) { return tolower(c); });
    s.erase(remove_if(s.begin(), s.end(), [](char c) { return !isalnum(c); }),
            s.end());

    string copy = s;
    reverse(copy.begin(), copy.end());

    return s == copy;
  }
};

TEST(Solution1, testCase1) {
  string s = "A man, a plan, a canal: Panama";

  Solution1 solution;
  EXPECT_EQ(solution.isPalindrome(s), true);
}

TEST(Solution1, testCase2) {
  string s = "raceacar";

  Solution1 solution;
  EXPECT_EQ(solution.isPalindrome(s), false);
}

TEST(Solution1, testCase3) {
  string s = " ";

  Solution1 solution;
  EXPECT_EQ(solution.isPalindrome(s), true);
}