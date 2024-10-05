#include <gtest/gtest.h>
#include <vector>

using namespace std;

class Solution1 {
public:
  int maxArea(vector<int> &height) {
    int result = 0;

    int left = 0;
    int right = height.size() - 1;
    while (left < right) {
      int w = right - left;
      int h = min(height[left], height[right]);
      result = max(result, w * h);

      if (height[left] < height[right]) {
        left++;
      } else {
        right--;
      }
    }

    return result;
  }
};

TEST(Solution1, testCase1) {
  vector<int> height = {1, 8, 6, 2, 5, 4, 8, 3, 7};

  Solution1 solution;
  EXPECT_EQ(solution.maxArea(height), 49);
}

TEST(Solution1, testCase2) {
  vector<int> height = {1, 1};

  Solution1 solution;
  EXPECT_EQ(solution.maxArea(height), 1);
}