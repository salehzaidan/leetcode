#include <forward_list>
#include <functional>
#include <gtest/gtest.h>

using namespace std;

class Solution1 {
  public:
    bool canFinish(int numCourses, vector<vector<int>> &prerequisites) {
        vector<forward_list<int>> adj(numCourses);
        for (auto &p : prerequisites) {
            int a = p[0];
            int b = p[1];
            adj[b].push_front(a);
        }

        enum State { UNVISITED, VISITING, VISITED };

        vector<State> state(adj.size(), UNVISITED);

        function<bool(int)> dfs = [&](int u) {
            state[u] = VISITING;

            for (int v : adj[u]) {
                switch (state[v]) {
                case UNVISITED:
                    if (dfs(v)) {
                        return true;
                    }
                    break;
                case VISITING:
                    return true;
                default:
                }
            }

            state[u] = VISITED;
            return false;
        };

        for (int u = 0; u < adj.size(); u++) {
            if (state[u] == UNVISITED) {
                if (dfs(u)) {
                    return false;
                }
            }
        }

        return true;
    }
};

class Solution1Test : public ::testing::Test {
  protected:
    Solution1 solution;
};

TEST_F(Solution1Test, TestCase1) {
    int numCourses = 2;
    vector<vector<int>> prerequisites = {{1, 0}};

    bool actual = solution.canFinish(numCourses, prerequisites);
    bool expected = true;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase2) {
    int numCourses = 2;
    vector<vector<int>> prerequisites = {{1, 0}, {0, 1}};

    bool actual = solution.canFinish(numCourses, prerequisites);
    bool expected = false;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase3) {
    int numCourses = 4;
    vector<vector<int>> prerequisites = {{1, 0}, {2, 0}, {3, 1}, {3, 2}};

    bool actual = solution.canFinish(numCourses, prerequisites);
    bool expected = true;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase4) {
    int numCourses = 4;
    vector<vector<int>> prerequisites = {{1, 0}, {2, 1}, {3, 2}, {1, 3}};

    bool actual = solution.canFinish(numCourses, prerequisites);
    bool expected = false;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase5) {
    int numCourses = 3;
    vector<vector<int>> prerequisites = {};

    bool actual = solution.canFinish(numCourses, prerequisites);
    bool expected = true;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase6) {
    int numCourses = 5;
    vector<vector<int>> prerequisites = {{1, 0}, {2, 1}, {3, 2}, {4, 3}};

    bool actual = solution.canFinish(numCourses, prerequisites);
    bool expected = true;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase7) {
    int numCourses = 6;
    vector<vector<int>> prerequisites = {{1, 0}, {2, 3}, {4, 5}};

    bool actual = solution.canFinish(numCourses, prerequisites);
    bool expected = true;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase8) {
    int numCourses = 1;
    vector<vector<int>> prerequisites = {{0, 0}};

    bool actual = solution.canFinish(numCourses, prerequisites);
    bool expected = false;

    EXPECT_EQ(actual, expected);
}