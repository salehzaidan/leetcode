#include <gtest/gtest.h>
#include <queue>
#include <vector>

using namespace std;

class Solution1 {
  public:
    int numIslands(const vector<vector<char>> &grid) {
        int rows = grid.size();
        int cols = grid.front().size();
        int result = 0;

        vector<vector<bool>> visited(rows, vector<bool>(cols, false));
        vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        for (int y = 0; y < rows; y++) {
            for (int x = 0; x < cols; x++) {
                if (grid[y][x] == '0' || visited[y][x]) {
                    continue;
                }

                queue<pair<int, int>> q;
                q.push({y, x});

                while (!q.empty()) {
                    auto u = q.front();
                    q.pop();

                    for (const auto &dir : directions) {
                        pair<int, int> v = {u.first + dir.first,
                                            u.second + dir.second};
                        if (v.first < 0 || v.first >= rows || v.second < 0 ||
                            v.second >= cols ||
                            grid[v.first][v.second] == '0') {
                            continue;
                        }

                        if (!visited[v.first][v.second]) {
                            visited[v.first][v.second] = true;
                            q.push(v);
                        }
                    }
                }

                result++;
            }
        }

        return result;
    }
};

class Solution1Test : public ::testing::Test {
  protected:
    Solution1 solution;
};

TEST_F(Solution1Test, TestCase1) {
    vector<vector<char>> grid = {{'1', '1', '1', '1', '0'},
                                 {'1', '1', '0', '1', '0'},
                                 {'1', '1', '0', '0', '0'},
                                 {'0', '0', '0', '0', '0'}};

    int actual = solution.numIslands(grid);
    int expected = 1;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase2) {
    vector<vector<char>> grid = {{'1', '1', '0', '0', '0'},
                                 {'1', '1', '0', '0', '0'},
                                 {'0', '0', '1', '0', '0'},
                                 {'0', '0', '0', '1', '1'}};

    int actual = solution.numIslands(grid);
    int expected = 3;

    EXPECT_EQ(actual, expected);
}

class Solution2 {
  public:
    int numIslands(const vector<vector<char>> &grid) {
        int rows = grid.size();
        int cols = grid.front().size();
        int result = 0;

        vector<vector<bool>> visited(rows, vector<bool>(cols, false));

        for (int y = 0; y < rows; y++) {
            for (int x = 0; x < cols; x++) {
                if (grid[y][x] == '0' || visited[y][x]) {
                    continue;
                }

                dfs(grid, visited, {y, x});
                result++;
            }
        }

        return result;
    }

  private:
    void dfs(const vector<vector<char>> &grid, vector<vector<bool>> &visited,
             pair<int, int> u) {
        int rows = grid.size();
        int cols = grid.front().size();
        static vector<pair<int, int>> directions = {
            {-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        visited[u.first][u.second] = true;

        for (const auto &dir : directions) {
            pair<int, int> v = {u.first + dir.first, u.second + dir.second};

            if (v.first < 0 || v.first >= rows || v.second < 0 ||
                v.second >= cols || grid[v.first][v.second] == '0') {
                continue;
            }

            if (!visited[v.first][v.second]) {
                dfs(grid, visited, v);
            }
        }
    }
};

class Solution2Test : public ::testing::Test {
  protected:
    Solution2 solution;
};

TEST_F(Solution2Test, TestCase1) {
    vector<vector<char>> grid = {{'1', '1', '1', '1', '0'},
                                 {'1', '1', '0', '1', '0'},
                                 {'1', '1', '0', '0', '0'},
                                 {'0', '0', '0', '0', '0'}};

    int actual = solution.numIslands(grid);
    int expected = 1;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution2Test, TestCase2) {
    vector<vector<char>> grid = {{'1', '1', '0', '0', '0'},
                                 {'1', '1', '0', '0', '0'},
                                 {'0', '0', '1', '0', '0'},
                                 {'0', '0', '0', '1', '1'}};

    int actual = solution.numIslands(grid);
    int expected = 3;

    EXPECT_EQ(actual, expected);
}