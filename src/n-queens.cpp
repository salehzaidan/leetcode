#include <algorithm>
#include <gtest/gtest.h>
#include <string>
#include <vector>

using namespace std;

class Solution1 {
  public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<pair<int, int>>> solutions;
        vector<pair<int, int>> positions;

        backtrack(n, solutions, positions, 0);

        return getResults(n, solutions);
    }

  private:
    void backtrack(int n, vector<vector<pair<int, int>>> &solutions,
                   vector<pair<int, int>> &positions, int row) {
        if (row == n) {
            solutions.push_back(positions);
            return;
        }

        for (int col = 0; col < n; col++) {
            pair<int, int> pos = {row, col};

            if (!isValid(positions, pos)) {
                continue;
            }

            positions.push_back(pos);
            backtrack(n, solutions, positions, row + 1);
            positions.pop_back();
        }
    }

    bool isValid(const vector<pair<int, int>> &positions, pair<int, int> pos) {
        for (const auto &existing : positions) {
            if (existing.first == pos.first) {
                return false;
            }

            if (existing.second == pos.second) {
                return false;
            }

            int dy = existing.first - pos.first;
            int dx = existing.second - pos.second;

            if (dy == dx) {
                return false;
            }

            if (dy == -dx) {
                return false;
            }
        }

        return true;
    }

    vector<vector<string>>
    getResults(int n, const vector<vector<pair<int, int>>> &solutions) {
        vector<vector<string>> result;
        for (const auto &solution : solutions) {
            vector<string> grid;
            for (int y = 0; y < n; y++) {
                string row;
                for (int x = 0; x < n; x++) {
                    bool exist =
                        any_of(solution.begin(), solution.end(),
                               [&](const auto &cell) {
                                   return cell.first == y && cell.second == x;
                               });
                    if (exist) {
                        row.push_back('Q');
                    } else {
                        row.push_back('.');
                    }
                }
                grid.push_back(row);
            }
            result.push_back(grid);
        }
        return result;
    }
};

class Solution1Test : public ::testing::Test {
  protected:
    Solution1 solution;
};

TEST_F(Solution1Test, TestCase1) {
    int n = 4;

    vector<vector<string>> actual = solution.solveNQueens(n);
    vector<vector<string>> expected = {{".Q..", "...Q", "Q...", "..Q."},
                                       {"..Q.", "Q...", "...Q", ".Q.."}};

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase2) {
    int n = 1;

    vector<vector<string>> actual = solution.solveNQueens(n);
    vector<vector<string>> expected = {{"Q"}};

    EXPECT_EQ(actual, expected);
}