#include <gtest/gtest.h>
#include <queue>
#include <vector>

using namespace std;

class Solution1 {
  public:
    int lastStoneWeight(vector<int> &stones) {
        priority_queue<int> q(stones.begin(), stones.end());

        while (q.size() >= 2) {
            int y = q.top();
            q.pop();
            int x = q.top();
            q.pop();

            if (x != y) {
                q.push(y - x);
            }
        }

        return q.empty() ? 0 : q.top();
    }
};

class Solution1Test : public ::testing::Test {
  protected:
    Solution1 solution;
};

TEST_F(Solution1Test, TestCase1) {
    vector<int> stones = {2, 7, 4, 1, 8, 1};

    int actual = solution.lastStoneWeight(stones);
    int expected = 1;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase2) {
    vector<int> stones = {1};

    int actual = solution.lastStoneWeight(stones);
    int expected = 1;

    EXPECT_EQ(actual, expected);
}