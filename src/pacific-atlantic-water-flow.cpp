#include <algorithm>
#include <functional>
#include <gtest/gtest.h>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

class Solution1 {
  public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>> &heights) {
        int rows = heights.size();
        int cols = heights.front().size();

        vector<vector<int>> result;
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));
        vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        function<pair<bool, bool>(pair<int, int>)> dfs = [&](pair<int, int> u) {
            visited[u.first][u.second] = true;

            bool canReachPacific = u.first == 0 || u.second == 0;
            bool canReachAtlantic = u.first == rows - 1 || u.second == cols - 1;

            for (auto dir : directions) {
                pair<int, int> v = {u.first + dir.first, u.second + dir.second};

                if (v.first < 0 || v.first >= rows || v.second < 0 ||
                    v.second >= cols || visited[v.first][v.second] ||
                    heights[v.first][v.second] > heights[u.first][u.second]) {
                    continue;
                }

                auto res = dfs(v);
                canReachPacific |= res.first;
                canReachAtlantic |= res.second;
            }

            return make_pair(canReachPacific, canReachAtlantic);
        };

        for (int y = 0; y < rows; y++) {
            for (int x = 0; x < cols; x++) {
                fill(visited.begin(), visited.end(), vector<bool>(cols, false));

                auto [canReachPacific, canReachAtlantic] = dfs({y, x});
                if (canReachPacific && canReachAtlantic) {
                    result.push_back({y, x});
                }
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
    vector<vector<int>> heights = {{1, 2, 2, 3, 5},
                                   {3, 2, 3, 4, 4},
                                   {2, 4, 5, 3, 1},
                                   {6, 7, 1, 4, 5},
                                   {5, 1, 1, 2, 4}};

    vector<vector<int>> actual = solution.pacificAtlantic(heights);
    vector<vector<int>> expected = {{0, 4}, {1, 3}, {1, 4}, {2, 2},
                                    {3, 0}, {3, 1}, {4, 0}};

    sort(actual.begin(), actual.end());
    sort(expected.begin(), expected.end());
    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase2) {
    vector<vector<int>> heights = {{1}};

    vector<vector<int>> actual = solution.pacificAtlantic(heights);
    vector<vector<int>> expected = {{0, 0}};

    sort(actual.begin(), actual.end());
    sort(expected.begin(), expected.end());
    EXPECT_EQ(actual, expected);
}

class Solution2 {
  public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>> &heights) {
        int rows = heights.size();
        int cols = heights.front().size();

        vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        vector<pair<int, int>> pacificBorders;
        vector<pair<int, int>> atlanticBorders;
        vector<vector<bool>> pacificReachable(rows, vector<bool>(cols, false));
        vector<vector<bool>> atlanticReachable(rows, vector<bool>(cols, false));
        for (int row = 0; row < rows; row++) {
            pacificBorders.push_back({row, 0});
            pacificReachable[row][0] = true;
            atlanticBorders.push_back({row, cols - 1});
            atlanticReachable[row][cols - 1] = true;
        }
        for (int col = 0; col < cols; col++) {
            pacificBorders.push_back({0, col});
            pacificReachable[0][col] = true;
            atlanticBorders.push_back({rows - 1, col});
            atlanticReachable[rows - 1][col] = true;
        }

        auto bfs = [&](const vector<pair<int, int>> &borders,
                       vector<vector<bool>> &reachable) {
            queue<pair<int, int>> q;
            for (auto border : borders) {
                q.push(border);
            }

            while (!q.empty()) {
                auto u = q.front();
                q.pop();

                for (auto dir : directions) {
                    pair<int, int> v = {u.first + dir.first,
                                        u.second + dir.second};
                    if (v.first < 0 || v.first >= rows || v.second < 0 ||
                        v.second >= cols || reachable[v.first][v.second] ||
                        heights[v.first][v.second] <
                            heights[u.first][u.second]) {
                        continue;
                    }

                    reachable[v.first][v.second] = true;
                    q.push(v);
                }
            }
        };

        bfs(pacificBorders, pacificReachable);
        bfs(atlanticBorders, atlanticReachable);

        vector<vector<int>> result;
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                if (pacificReachable[row][col] && atlanticReachable[row][col]) {
                    result.push_back({row, col});
                }
            }
        }

        return result;
    }
};

class Solution2Test : public ::testing::Test {
  protected:
    Solution2 solution;
};

TEST_F(Solution2Test, TestCase1) {
    vector<vector<int>> heights = {{1, 2, 2, 3, 5},
                                   {3, 2, 3, 4, 4},
                                   {2, 4, 5, 3, 1},
                                   {6, 7, 1, 4, 5},
                                   {5, 1, 1, 2, 4}};

    vector<vector<int>> actual = solution.pacificAtlantic(heights);
    vector<vector<int>> expected = {{0, 4}, {1, 3}, {1, 4}, {2, 2},
                                    {3, 0}, {3, 1}, {4, 0}};

    sort(actual.begin(), actual.end());
    sort(expected.begin(), expected.end());
    EXPECT_EQ(actual, expected);
}

TEST_F(Solution2Test, TestCase2) {
    vector<vector<int>> heights = {{1}};

    vector<vector<int>> actual = solution.pacificAtlantic(heights);
    vector<vector<int>> expected = {{0, 0}};

    sort(actual.begin(), actual.end());
    sort(expected.begin(), expected.end());
    EXPECT_EQ(actual, expected);
}