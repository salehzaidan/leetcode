#include <gtest/gtest.h>
#include <stack>
#include <vector>

using namespace std;

class Solution1 {
public:
  int largestRectangleArea(const vector<int> &heights) {
    int maxArea = 0;
    stack<int> indices;

    for (int i = 0; i <= heights.size(); i++) {
      int height = i == heights.size() ? 0 : heights[i];
      while (!indices.empty() && height < heights[indices.top()]) {
        int j = indices.top();
        indices.pop();

        int width;
        if (indices.empty()) {
          width = i;
        } else {
          width = i - indices.top() - 1;
        }
        maxArea = max(maxArea, width * heights[j]);
      }

      indices.push(i);
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
