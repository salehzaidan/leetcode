#include <functional>
#include <gtest/gtest.h>

using namespace std;

class Solution1 {
  public:
    void solve(vector<vector<char>> &board) {
        int rows = board.size();
        int cols = board.front().size();

        vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));
        vector<pair<int, int>> regions;

        function<bool(vector<pair<int, int>> &, pair<int, int>)> dfs =
            [&](vector<pair<int, int>> &regions, pair<int, int> u) {
                visited[u.first][u.second] = true;

                bool onBorder = u.first == 0 || u.first == rows - 1 ||
                                u.second == 0 || u.second == cols - 1;

                for (const auto &dir : directions) {
                    pair<int, int> v = {u.first + dir.first,
                                        u.second + dir.second};

                    if (v.first < 0 || v.first >= rows || v.second < 0 ||
                        v.second >= cols || board[v.first][v.second] != 'O') {
                        continue;
                    }

                    if (!visited[v.first][v.second]) {
                        onBorder |= dfs(regions, v);
                    }
                }

                regions.push_back(u);

                return onBorder;
            };

        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                if (board[row][col] == 'O' && !visited[row][col]) {
                    vector<pair<int, int>> regions;
                    if (dfs(regions, {row, col})) {
                        continue;
                    }

                    for (auto &cell : regions) {
                        board[cell.first][cell.second] = 'X';
                    }
                }
            }
        }
    }
};

class Solution1Test : public ::testing::Test {
  protected:
    Solution1 solution;
};

TEST_F(Solution1Test, TestCase1) {
    vector<vector<char>> board = {{'X', 'X', 'X', 'X'},
                                  {'X', 'O', 'O', 'X'},
                                  {'X', 'X', 'O', 'X'},
                                  {'X', 'O', 'X', 'X'}};

    solution.solve(board);
    vector<vector<char>> expected = {{'X', 'X', 'X', 'X'},
                                     {'X', 'X', 'X', 'X'},
                                     {'X', 'X', 'X', 'X'},
                                     {'X', 'O', 'X', 'X'}};

    EXPECT_EQ(board, expected);
}

TEST_F(Solution1Test, TestCase2) {
    vector<vector<char>> board = {{'X', 'O', 'X', 'X'},
                                  {'X', 'O', 'O', 'X'},
                                  {'X', 'O', 'X', 'X'},
                                  {'X', 'X', 'X', 'X'}};

    solution.solve(board);
    vector<vector<char>> expected = {{'X', 'O', 'X', 'X'},
                                     {'X', 'O', 'O', 'X'},
                                     {'X', 'O', 'X', 'X'},
                                     {'X', 'X', 'X', 'X'}};
    EXPECT_EQ(board, expected);
}

class Solution2 {
  public:
    void solve(vector<vector<char>> &board) {
        int rows = board.size();
        int cols = board.front().size();

        vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));
        vector<vector<bool>> marked(rows, vector<bool>(cols, false));

        function<void(pair<int, int>)> dfs = [&](pair<int, int> u) {
            visited[u.first][u.second] = true;

            for (const auto &dir : directions) {
                pair<int, int> v = {u.first + dir.first, u.second + dir.second};

                if (v.first < 0 || v.first >= rows || v.second < 0 ||
                    v.second >= cols || board[v.first][v.second] != 'O') {
                    continue;
                }

                if (!visited[v.first][v.second]) {
                    dfs(v);
                }
            }

            marked[u.first][u.second] = true;
        };

        for (int row = 0; row < rows; row++) {
            if (board[row][0] == 'O') {
                dfs({row, 0});
            }
            if (board[row][cols - 1] == 'O') {
                dfs({row, cols - 1});
            }
        }

        for (int col = 0; col < cols; col++) {
            if (board[0][col] == 'O') {
                dfs({0, col});
            }
            if (board[rows - 1][col] == 'O') {
                dfs({rows - 1, col});
            }
        }

        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                if (!marked[row][col]) {
                    board[row][col] = 'X';
                }
            }
        }
    }
};

class Solution2Test : public ::testing::Test {
  protected:
    Solution2 solution;
};

TEST_F(Solution2Test, TestCase1) {
    vector<vector<char>> board = {{'X', 'X', 'X', 'X'},
                                  {'X', 'O', 'O', 'X'},
                                  {'X', 'X', 'O', 'X'},
                                  {'X', 'O', 'X', 'X'}};

    solution.solve(board);
    vector<vector<char>> expected = {{'X', 'X', 'X', 'X'},
                                     {'X', 'X', 'X', 'X'},
                                     {'X', 'X', 'X', 'X'},
                                     {'X', 'O', 'X', 'X'}};

    EXPECT_EQ(board, expected);
}

TEST_F(Solution2Test, TestCase2) {
    vector<vector<char>> board = {{'X', 'O', 'X', 'X'},
                                  {'X', 'O', 'O', 'X'},
                                  {'X', 'O', 'X', 'X'},
                                  {'X', 'X', 'X', 'X'}};

    solution.solve(board);
    vector<vector<char>> expected = {{'X', 'O', 'X', 'X'},
                                     {'X', 'O', 'O', 'X'},
                                     {'X', 'O', 'X', 'X'},
                                     {'X', 'X', 'X', 'X'}};
    EXPECT_EQ(board, expected);
}