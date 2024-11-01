#include <gtest/gtest.h>
#include <queue>
#include <vector>

using namespace std;

class Solution1 {
  public:
    vector<vector<int>> kClosest(vector<vector<int>> &points, int k) {
        auto comp = [](const vector<int> &a, const vector<int> &b) {
            long diff1 = a[0] * a[0] + a[1] * a[1];
            long diff2 = b[0] * b[0] + b[1] * b[1];
            return diff1 * diff1 < diff2 * diff2;
        };

        priority_queue<vector<int>, vector<vector<int>>, decltype(comp)> q(
            comp, points);
        while (q.size() > k) {
            q.pop();
        }

        vector<vector<int>> result;
        while (!q.empty()) {
            result.push_back(q.top());
            q.pop();
        }

        return result;
    }
};

class Solution1Test : public ::testing::Test {
  protected:
    Solution1 solution;
};

auto pointComparator = [](const vector<int> &a, const vector<int> &b) {
    int diff1 = a[0] * a[0] + a[1] * a[1];
    int diff2 = b[0] * b[0] + b[1] * b[1];
    return diff1 * diff1 < diff2 * diff2;
};

TEST_F(Solution1Test, TestCase1) {
    vector<vector<int>> points = {{1, 3}, {-2, 2}};
    int k = 1;

    vector<vector<int>> actual = solution.kClosest(points, k);
    vector<vector<int>> expected = {{-2, 2}};

    sort(actual.begin(), actual.end(), pointComparator);
    sort(expected.begin(), expected.end(), pointComparator);
    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase2) {
    vector<vector<int>> points = {{3, 3}, {5, -1}, {-2, 4}};
    int k = 2;

    vector<vector<int>> actual = solution.kClosest(points, k);
    vector<vector<int>> expected = {{3, 3}, {-2, 4}};

    sort(actual.begin(), actual.end(), pointComparator);
    sort(expected.begin(), expected.end(), pointComparator);
    EXPECT_EQ(actual, expected);
}