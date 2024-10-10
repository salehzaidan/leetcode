#include <gtest/gtest.h>
#include <stack>
#include <string>
#include <vector>

using namespace std;

class Solution1 {
  public:
    int evalRPN(const vector<string> &tokens) {
        stack<int> s;

        for (const string &token : tokens) {
            if (token == "+" || token == "-" || token == "*" || token == "/") {
                int b = s.top();
                s.pop();
                int a = s.top();
                s.pop();

                if (token == "+") {
                    s.push(a + b);
                } else if (token == "-") {
                    s.push(a - b);
                } else if (token == "*") {
                    s.push(a * b);
                } else {
                    s.push(a / b);
                }
            } else {
                int value = stoi(token);
                s.push(value);
            }
        }

        return s.top();
    }
};

TEST(Solution1, testCase1) {
    vector<string> tokens = {"2", "1", "+", "3", "*"};

    Solution1 solution;
    EXPECT_EQ(solution.evalRPN(tokens), 9);
}

TEST(Solution1, testCase2) {
    vector<string> tokens = {"4", "13", "5", "/", "+"};

    Solution1 solution;
    EXPECT_EQ(solution.evalRPN(tokens), 6);
}

TEST(Solution1, testCase3) {
    vector<string> tokens = {"10", "6", "9",  "3", "+", "-11", "*",
                             "/",  "*", "17", "+", "5", "+"};

    Solution1 solution;
    EXPECT_EQ(solution.evalRPN(tokens), 22);
}