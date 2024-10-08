#include <gtest/gtest.h>

using namespace std;

class Solution1 {
public:
  bool searchMatrix(const vector<vector<int>> &matrix, int target) {
    int rows = matrix.size();
    int cols = matrix.front().size();

    int left = 0;
    int right = rows * cols - 1;
    while (left <= right) {
      int mid = left + (right - left) / 2;
      int i = mid / cols;
      int j = mid % cols;
      if (matrix[i][j] == target) {
        return true;
      } else if (matrix[i][j] < target) {
        left = mid + 1;
      } else {
        right = mid - 1;
      }
    }

    return false;
  }
};

class Solution1Test : public ::testing::Test {
protected:
  Solution1 solution;
};

TEST_F(Solution1Test, TestCase1) {
  vector<vector<int>> matrix = {
      {1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}};
  int target = 3;

  int actual = solution.searchMatrix(matrix, target);
  bool expected = true;

  EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase2) {
  vector<vector<int>> matrix = {
      {1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}};
  int target = 13;

  int actual = solution.searchMatrix(matrix, target);
  bool expected = false;

  EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase3) {
  vector<vector<int>> matrix = {{1}};
  int target = 2;

  int actual = solution.searchMatrix(matrix, target);
  bool expected = false;

  EXPECT_EQ(actual, expected);
}