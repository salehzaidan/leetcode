#include <gtest/gtest.h>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right)
        : val(x), left(left), right(right) {}
};

class Solution {
  public:
    vector<int> inorderTraversal(TreeNode *root) {
        vector<int> values;
        traverse(root, values);
        return values;
    }

  private:
    void traverse(TreeNode *node, vector<int> &values) {
        if (node == nullptr) {
            return;
        }

        traverse(node->left, values);
        values.push_back(node->val);
        traverse(node->right, values);
    }
};

TEST(Solution, InorderTraversal1) {
    Solution solution;
    TreeNode *node1 = new TreeNode(3);
    TreeNode *node2 = new TreeNode(2, node1, nullptr);
    TreeNode *node3 = new TreeNode(1, nullptr, node2);
    vector<int> expected{1, 3, 2};
    vector<int> actual = solution.inorderTraversal(node3);
    EXPECT_EQ(expected, actual);
    delete node1;
    delete node2;
    delete node3;
}

TEST(Solution, InorderTraversal2) {
    Solution solution;
    TreeNode *node = nullptr;
    vector<int> expected{};
    vector<int> actual = solution.inorderTraversal(node);
    EXPECT_EQ(expected, actual);
}

TEST(Solution, InorderTraversal3) {
    Solution solution;
    TreeNode *node = new TreeNode(1);
    vector<int> expected{1};
    vector<int> actual = solution.inorderTraversal(node);
    EXPECT_EQ(expected, actual);
    delete node;
}
