#include <gtest/gtest.h>
#include <stack>
#include <vector>

using namespace std;

class Solution1 {
public:
  int largestRectangleArea(const vector<int> &heights) {
    struct State {
      int index;
      int height;
    };

    int maxArea = 0;
    stack<State> state;

    for (int i = 0; i < heights.size(); i++) {
      int start = i;

      while (!state.empty() && state.top().height > heights[i]) {
        State s = state.top();
        state.pop();
        int width = (i - s.index);
        maxArea = max(maxArea, s.height * width);
        start = s.index;
      }

      state.push(State{start, heights[i]});
    }

    while (!state.empty()) {
      State s = state.top();
      int width = ((int)heights.size() - s.index);
      maxArea = max(maxArea, s.height * width);
      state.pop();
    }

    return maxArea;
  }
};

TEST(Solution1, testCase1) {
  vector<int> heights = {2, 1, 5, 6, 2, 3};

  Solution1 solution;
  EXPECT_EQ(solution.largestRectangleArea(heights), 10);
}

TEST(Solution1, testCase2) {
  vector<int> heights = {2, 4};

  Solution1 solution;
  EXPECT_EQ(solution.largestRectangleArea(heights), 4);
}
