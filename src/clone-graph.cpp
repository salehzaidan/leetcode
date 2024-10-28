#include <functional>
#include <gtest/gtest.h>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Node {
  public:
    int val;
    vector<Node *> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node *>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node *>();
    }
    Node(int _val, vector<Node *> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

Node *createGraph(const vector<vector<int>> &edges) {
    vector<Node *> nodes(edges.size(), nullptr);

    for (int current = 1; current <= edges.size(); current++) {
        if (nodes[current - 1] == nullptr) {
            nodes[current - 1] = new Node(current);
        }

        Node *u = nodes[current - 1];
        for (int neighbor : edges[current - 1]) {
            if (nodes[neighbor - 1] == nullptr) {
                nodes[neighbor - 1] = new Node(neighbor);
            }
            Node *v = nodes[neighbor - 1];
            u->neighbors.push_back(v);
        }
    }

    return nodes.front();
}

bool compareGraph(Node *node1, Node *node2) {
    unordered_set<Node *> visited;

    function<bool(Node *, Node *)> compareNode = [&](Node *u1, Node *u2) {
        visited.insert(u1);
        for (int i = 0; i < u1->neighbors.size(); i++) {
            Node *v1 = u1->neighbors[i];
            if (i >= u2->neighbors.size()) {
                return false;
            }

            Node *v2 = u2->neighbors[i];
            if (v1->val != v2->val) {
                return false;
            }

            if (!visited.contains(v1)) {
                compareNode(v1, v2);
            }
        }

        return true;
    };

    return compareNode(node1, node2);
}

void deleteGraph(Node *node) {
    if (node == nullptr) {
        return;
    }

    unordered_set<Node *> visited;

    function<void(Node *)> deleteNode = [&](Node *u) {
        visited.insert(u);
        for (Node *v : u->neighbors) {
            if (!visited.contains(v)) {
                deleteNode(v);
            }
        }
        delete u;
    };

    deleteNode(node);
}

TEST(TestGraphUtils, GeneralGraph) {
    Node *node = createGraph({{2, 4}, {1, 3}, {2, 4}, {1, 3}});
    deleteGraph(node);
}

class Solution1 {
  public:
    Node *cloneGraph(Node *node) {
        if (node == nullptr) {
            return nullptr;
        }

        unordered_map<Node *, Node *> clones;

        function<Node *(Node *)> cloneNode = [&](Node *u) {
            if (clones.contains(u)) {
                return clones[u];
            }

            clones[u] = new Node(u->val);
            for (Node *v : u->neighbors) {
                clones[u]->neighbors.push_back(cloneNode(v));
            }

            return clones[u];
        };

        return cloneNode(node);
    }
};

class Solution1Test : public ::testing::Test {
  protected:
    Solution1 solution;
};

TEST_F(Solution1Test, TestCase1) {
    Node *node = createGraph({{2, 4}, {1, 3}, {2, 4}, {1, 3}});

    Node *clone = solution.cloneGraph(node);

    EXPECT_TRUE(compareGraph(node, clone));

    deleteGraph(node);
    deleteGraph(clone);
}