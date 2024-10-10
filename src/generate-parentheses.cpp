#include <gtest/gtest.h>
#include <string>
#include <vector>

using namespace std;

class Solution1 {
  public:
    vector<string> generateParenthesis(int n) {
        vector<string> parenthesis;

        string s;
        s.reserve(2 * n);
        backtrack(n, parenthesis, 0, 0, s);

        return parenthesis;
    }

  private:
    void backtrack(int n, vector<string> &parenthesis, int totalScope,
                   int openScope, string &s) {
        if (totalScope == n && openScope == 0) {
            parenthesis.push_back(s);
            return;
        }

        s += '(';
        if (totalScope < n) {
            backtrack(n, parenthesis, totalScope + 1, openScope + 1, s);
        }
        s.erase(s.length() - 1, 1);

        s += ')';
        if (openScope > 0) {
            backtrack(n, parenthesis, totalScope, openScope - 1, s);
        }
        s.erase(s.length() - 1, 1);
    }
};

TEST(Solution1, testCase1) {
    vector<string> expected = {"((()))", "(()())", "(())()", "()(())",
                               "()()()"};

    Solution1 solution;
    EXPECT_EQ(solution.generateParenthesis(3), expected);
}

TEST(Solution1, testCase2) {
    vector<string> expected = {"()"};

    Solution1 solution;
    EXPECT_EQ(solution.generateParenthesis(1), expected);
}