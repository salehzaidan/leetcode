#include <gtest/gtest.h>
#include <stack>
#include <string>

using namespace std;

class Solution1 {
  public:
    bool isValid(string s) {
        stack<char> opens;

        for (const char &c : s) {
            if (c == '(' || c == '[' || c == '{') {
                opens.push(c);
            } else {
                if (opens.empty()) {
                    return false;
                }

                char top = opens.top();
                if (!(top == '(' && c == ')' || top == '[' && c == ']' ||
                      top == '{' && c == '}')) {
                    return false;
                }

                opens.pop();
            }
        }

        return opens.empty();
    }
};

TEST(Solution1, testCase1) {
    string s = "()";

    Solution1 solution;
    EXPECT_EQ(solution.isValid(s), true);
}

TEST(Solution1, testCase2) {
    string s = "()[]{}";

    Solution1 solution;
    EXPECT_EQ(solution.isValid(s), true);
}

TEST(Solution1, testCase3) {
    string s = "(]";

    Solution1 solution;
    EXPECT_EQ(solution.isValid(s), false);
}

TEST(Solution1, testCase4) {
    string s = "([])";

    Solution1 solution;
    EXPECT_EQ(solution.isValid(s), true);
}

TEST(Solution1, testCase5) {
    string s = "{";

    Solution1 solution;
    EXPECT_EQ(solution.isValid(s), false);
}

TEST(Solution1, testCase6) {
    string s = ")";

    Solution1 solution;
    EXPECT_EQ(solution.isValid(s), false);
}