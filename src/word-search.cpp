#include <gtest/gtest.h>
#include <vector>

using namespace std;

class Solution1 {
  public:
    bool exist(vector<vector<char>> &board, string word) {
        int rows = board.size();
        int cols = board.front().size();

        vector<vector<bool>> visited(rows, vector<bool>(cols, false));

        for (int y = 0; y < board.size(); y++) {
            for (int x = 0; x < board.front().size(); x++) {
                if (word.front() == board[y][x]) {
                    if (backtrack(board, word, visited, {y, x}, 0)) {
                        return true;
                    }
                }
            }
        }

        return false;
    }

  private:
    bool backtrack(const vector<vector<char>> &board, const string &word,
                   vector<vector<bool>> &visited, pair<int, int> pos,
                   int index) {
        if (index == word.size()) {
            return true;
        }

        int rows = board.size();
        int cols = board.front().size();

        if (pos.first < 0 || pos.first >= rows || pos.second < 0 ||
            pos.second >= cols || board[pos.first][pos.second] != word[index] ||
            visited[pos.first][pos.second]) {
            return false;
        }

        visited[pos.first][pos.second] = true;
        static const vector<pair<int, int>> directions = {
            {-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        for (const auto &dir : directions) {
            pair<int, int> next = {pos.first + dir.first,
                                   pos.second + dir.second};
            if (backtrack(board, word, visited, next, index + 1)) {
                return true;
            }
        }

        visited[pos.first][pos.second] = false;
        return false;
    }
};

class Solution1Test : public ::testing::Test {
  protected:
    Solution1 solution;
};

TEST_F(Solution1Test, TestCase1) {
    vector<vector<char>> board = {
        {'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}};
    string word = "ABCCED";

    bool actual = solution.exist(board, word);
    bool expected = true;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase2) {
    vector<vector<char>> board = {
        {'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}};
    string word = "SEE";

    bool actual = solution.exist(board, word);
    bool expected = true;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase3) {
    vector<vector<char>> board = {
        {'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}};
    string word = "ABCB";

    bool actual = solution.exist(board, word);
    bool expected = false;

    EXPECT_EQ(actual, expected);
}