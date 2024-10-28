#include <gtest/gtest.h>
#include <queue>
#include <vector>

using namespace std;

class Solution1 {
  public:
    int orangesRotting(vector<vector<int>> grid) {
        const int EMPTY = 0;
        const int FRESH = 1;
        const int ROTTEN = 2;

        int rows = grid.size();
        int cols = grid.front().size();
        int freshCount = 0;
        queue<pair<int, int>> q;
        vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                switch (grid[row][col]) {
                case FRESH:
                    freshCount++;
                    break;
                case ROTTEN:
                    q.push({row, col});
                    break;
                }
            }
        }

        int time = 0;

        while (!q.empty()) {
            int levelSize = q.size();
            int oldFreshCount = freshCount;

            for (int i = 0; i < levelSize; i++) {
                auto u = q.front();
                q.pop();

                for (auto dir : directions) {
                    pair<int, int> v = {u.first + dir.first,
                                        u.second + dir.second};

                    if (v.first < 0 || v.first >= rows || v.second < 0 ||
                        v.second >= cols || grid[v.first][v.second] != FRESH) {
                        continue;
                    }

                    grid[v.first][v.second] = ROTTEN;
                    freshCount--;
                    q.push(v);
                }
            }

            if (freshCount < oldFreshCount) {
                time++;
            }
        }

        return freshCount == 0 ? time : -1;
    }
};

class Solution1Test : public ::testing::Test {
  protected:
    Solution1 solution;
};

TEST_F(Solution1Test, TestCase1) {
    vector<vector<int>> grid = {{2, 1, 1}, {1, 1, 0}, {0, 1, 1}};

    int actual = solution.orangesRotting(grid);
    int expected = 4;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase2) {
    vector<vector<int>> grid = {{2, 1, 1}, {0, 1, 1}, {1, 0, 1}};

    int actual = solution.orangesRotting(grid);
    int expected = -1;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase3) {
    vector<vector<int>> grid = {{0, 2}};

    int actual = solution.orangesRotting(grid);
    int expected = 0;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase4) {
    vector<vector<int>> grid = {{2, 1, 1}, {1, 1, 0}, {0, 1, 2}};

    int actual = solution.orangesRotting(grid);
    int expected = 2;

    EXPECT_EQ(actual, expected);
}