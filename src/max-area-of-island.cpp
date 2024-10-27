#include <gtest/gtest.h>

using namespace std;

class Solution1 {
  public:
    int maxAreaOfIsland(vector<vector<int>> &grid) {
        int rows = grid.size();
        int cols = grid.front().size();
        int maxArea = 0;

        vector<vector<bool>> visited(rows, vector<bool>(cols, false));

        for (int y = 0; y < rows; y++) {
            for (int x = 0; x < cols; x++) {
                if (grid[y][x] == 0 || visited[y][x]) {
                    continue;
                }

                pair<int, int> s = {y, x};
                int area = dfs(grid, visited, s);
                maxArea = max(maxArea, area);
            }
        }

        return maxArea;
    }

  private:
    int dfs(const vector<vector<int>> &grid, vector<vector<bool>> &visited,
            pair<int, int> u) {
        int rows = grid.size();
        int cols = grid.front().size();
        static vector<pair<int, int>> directions = {
            {-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        visited[u.first][u.second] = true;

        int area = 1;

        for (const auto &dir : directions) {
            pair<int, int> v = {u.first + dir.first, u.second + dir.second};

            if (v.first < 0 || v.first >= rows || v.second < 0 ||
                v.second >= cols || grid[v.first][v.second] == 0) {
                continue;
            }

            if (!visited[v.first][v.second]) {
                area += dfs(grid, visited, v);
            }
        }

        return area;
    }
};

class Solution1Test : public ::testing::Test {
  protected:
    Solution1 solution;
};

TEST_F(Solution1Test, TestCase1) {
    vector<vector<int>> grid = {{0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
                                {0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0},
                                {0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0}};

    int actual = solution.maxAreaOfIsland(grid);
    int expected = 6;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase2) {
    vector<vector<int>> grid = {{0, 0, 0, 0, 0, 0, 0, 0}};

    int actual = solution.maxAreaOfIsland(grid);
    int expected = 0;

    EXPECT_EQ(actual, expected);
}