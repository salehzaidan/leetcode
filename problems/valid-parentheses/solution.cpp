#include <gtest/gtest.h>
#include <stack>

using namespace std;

class Solution {
  public:
    bool isValid(string s) {
        stack<char> openings;

        for (char ch : s) {
            if (ch == '(' || ch == '{' || ch == '[') {
                openings.push(ch);
                continue;
            }

            if (openings.empty()) {
                return false;
            }

            if (((ch == ')' && openings.top() == '(') ||
                 (ch == '}' && openings.top() == '{') ||
                 (ch == ']' && openings.top() == '['))) {
                openings.pop();
                continue;
            }

            return false;
        }

        return openings.empty();
    }
};

TEST(Solution, IsValid1) {
    Solution solution;
    bool expected = true;
    bool actual = solution.isValid("()");
    EXPECT_EQ(expected, actual);
}

TEST(Solution, IsValid2) {
    Solution solution;
    bool expected = true;
    bool actual = solution.isValid("()[]{}");
    EXPECT_EQ(expected, actual);
}

TEST(Solution, IsValid3) {
    Solution solution;
    bool expected = false;
    bool actual = solution.isValid("(]");
    EXPECT_EQ(expected, actual);
}

TEST(Solution, IsValid4) {
    Solution solution;
    bool expected = false;
    bool actual = solution.isValid("(])");
    EXPECT_EQ(expected, actual);
}
