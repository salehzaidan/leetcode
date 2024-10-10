#include <gtest/gtest.h>
#include <stack>
#include <vector>

using namespace std;

class Solution1 {
  public:
    vector<int> dailyTemperatures(const vector<int> &temperatures) {
        vector<int> days(temperatures.size());

        stack<int> indices;
        indices.push(0);

        for (int i = 1; i < temperatures.size(); i++) {
            while (!indices.empty() &&
                   temperatures[i] > temperatures[indices.top()]) {
                days[indices.top()] = i - indices.top();
                indices.pop();
            }

            indices.push(i);
        }

        return days;
    }
};

TEST(Solution1, testCase1) {
    vector<int> temperatures = {73, 74, 75, 71, 69, 72, 76, 73};

    vector<int> expected = {1, 1, 4, 2, 1, 1, 0, 0};

    Solution1 solution;
    EXPECT_EQ(solution.dailyTemperatures(temperatures), expected);
}

TEST(Solution1, testCase2) {
    vector<int> temperatures = {30, 40, 50, 60};

    vector<int> expected = {1, 1, 1, 0};

    Solution1 solution;
    EXPECT_EQ(solution.dailyTemperatures(temperatures), expected);
}

TEST(Solution1, testCase3) {
    vector<int> temperatures = {30, 60, 90};

    vector<int> expected = {1, 1, 0};

    Solution1 solution;
    EXPECT_EQ(solution.dailyTemperatures(temperatures), expected);
}