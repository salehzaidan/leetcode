#include <forward_list>
#include <gtest/gtest.h>
#include <stdexcept>
#include <vector>

using namespace std;

class Solution1 {
  public:
    vector<int> findRedundantConnection(vector<vector<int>> &edges) {
        vector<forward_list<int>> adj(edges.size() + 1);
        vector<bool> visited(adj.size(), false);

        function<bool(int, int)> dfs = [&](int u, int parent) {
            visited[u] = true;

            for (int v : adj[u]) {
                if (!visited[v]) {
                    if (dfs(v, u)) {
                        return true;
                    }
                } else if (v != parent) {
                    return true;
                }
            }

            return false;
        };

        for (auto &edge : edges) {
            fill(visited.begin(), visited.end(), false);

            int a = edge[0];
            int b = edge[1];
            adj[b].push_front(a);
            adj[a].push_front(b);

            if (dfs(a, -1)) {
                return edge;
            }
        }

        throw runtime_error("Unreachable");
    }
};

class Solution1Test : public ::testing::Test {
  protected:
    Solution1 solution;
};

TEST_F(Solution1Test, TestCase1) {
    vector<vector<int>> edges = {{1, 2}, {1, 3}, {2, 3}};

    vector<int> actual = solution.findRedundantConnection(edges);
    vector<int> expected = {2, 3};

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase2) {
    vector<vector<int>> edges = {{1, 2}, {2, 3}, {3, 4}, {1, 4}, {1, 5}};

    vector<int> actual = solution.findRedundantConnection(edges);
    vector<int> expected = {1, 4};

    EXPECT_EQ(actual, expected);
}