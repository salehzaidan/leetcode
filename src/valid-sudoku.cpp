#include <gtest/gtest.h>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution1 {
  public:
    bool isValidSudoku(const vector<vector<char>> &board) {
        for (const vector<char> &row : board) {
            unordered_map<char, int> freq;
            for (char cell : row) {
                if (cell == '.') {
                    continue;
                }

                int &count = freq[cell];
                count++;
                if (count > 1) {
                    return false;
                }
            }
        }

        for (int col = 0; col < board.front().size(); col++) {
            unordered_map<char, int> freq;
            for (const vector<char> &row : board) {
                char cell = row[col];
                if (cell == '.') {
                    continue;
                }

                int &count = freq[cell];
                count++;
                if (count > 1) {
                    return false;
                }
            }
        }

        const int SUB_BOX_SIZE = 3;
        for (int i = 0; i < board.size(); i += SUB_BOX_SIZE) {
            for (int j = 0; j < board.front().size(); j += SUB_BOX_SIZE) {
                unordered_map<char, int> freq;
                for (int x = i; x < i + SUB_BOX_SIZE; x++) {
                    for (int y = j; y < j + SUB_BOX_SIZE; y++) {
                        char cell = board[x][y];
                        if (cell == '.') {
                            continue;
                        }

                        int &count = freq[cell];
                        count++;
                        if (count > 1) {
                            return false;
                        }
                    }
                }
            }
        }

        return true;
    }
};

TEST(Solution1, testCase1) {
    vector<vector<char>> board = {
        {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
        {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
        {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
        {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
        {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
        {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
        {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
        {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
        {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};

    Solution1 solution;
    EXPECT_EQ(solution.isValidSudoku(board), true);
}

TEST(Solution1, testCase2) {
    vector<vector<char>> board = {
        {'8', '3', '.', '.', '7', '.', '.', '.', '.'},
        {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
        {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
        {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
        {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
        {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
        {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
        {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
        {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};

    Solution1 solution;
    EXPECT_EQ(solution.isValidSudoku(board), false);
}