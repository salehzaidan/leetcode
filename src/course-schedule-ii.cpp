#include <forward_list>
#include <functional>
#include <gtest/gtest.h>

using namespace std;

class Solution1 {
  public:
    vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites) {
        vector<forward_list<int>> adj(numCourses);
        for (auto &p : prerequisites) {
            int a = p[0];
            int b = p[1];
            adj[b].push_front(a);
        }

        enum State { UNVISITED, VISITING, VISITED };

        vector<State> state(adj.size(), UNVISITED);
        forward_list<int> courses;

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
            courses.push_front(u);
            return false;
        };

        for (int u = 0; u < adj.size(); u++) {
            if (state[u] == UNVISITED) {
                if (dfs(u)) {
                    return {};
                }
            }
        }

        return vector<int>(courses.begin(), courses.end());
    }
};

class Solution1Test : public ::testing::Test {
  protected:
    Solution1 solution;
};

TEST_F(Solution1Test, TestCase1) {
    int numCourses = 2;
    vector<vector<int>> prerequisites = {{1, 0}};

    vector<int> actual = solution.findOrder(numCourses, prerequisites);
    vector<int> expected = {0, 1};

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase2) {
    int numCourses = 4;
    vector<vector<int>> prerequisites = {{1, 0}, {2, 0}, {3, 1}, {3, 2}};

    vector<int> actual = solution.findOrder(numCourses, prerequisites);
    vector<int> expected = {0, 1, 2, 3};

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase3) {
    int numCourses = 1;
    vector<vector<int>> prerequisites = {};

    vector<int> actual = solution.findOrder(numCourses, prerequisites);
    vector<int> expected = {0};

    EXPECT_EQ(actual, expected);
}