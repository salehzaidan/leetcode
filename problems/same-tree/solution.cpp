#include <gtest/gtest.h>
#include <optional>

#include "treenode.hpp"

using namespace std;

class Solution {
  public:
    bool isSameTree(TreeNode *p, TreeNode *q) {
        vector<optional<int>> tree1;
        vector<optional<int>> tree2;

        traverse(p, tree1);
        traverse(q, tree2);

        return tree1 == tree2;
    }

  private:
    void traverse(TreeNode *node, vector<optional<int>> &values) {
        if (node == nullptr) {
            values.push_back(nullopt);
            return;
        }

        values.push_back(node->val);
        traverse(node->left, values);
        traverse(node->right, values);
    }
};

TEST(Solution, IsSameTree1) {
    Solution solution;
    TreeNode *node1 = new TreeNode(2);
    TreeNode *node2 = new TreeNode(3);
    TreeNode *node3 = new TreeNode(1, node1, node2);
    TreeNode *node4 = new TreeNode(2);
    TreeNode *node5 = new TreeNode(3);
    TreeNode *node6 = new TreeNode(1, node4, node5);
    bool expected = true;
    bool actual = solution.isSameTree(node3, node6);
    EXPECT_EQ(expected, actual);
    delete node1;
    delete node2;
    delete node3;
    delete node4;
    delete node5;
    delete node6;
}

TEST(Solution, IsSameTree2) {
    Solution solution;
    TreeNode *node1 = new TreeNode(2);
    TreeNode *node2 = new TreeNode(1, node1, nullptr);
    TreeNode *node3 = new TreeNode(2);
    TreeNode *node4 = new TreeNode(1, nullptr, node3);
    bool expected = false;
    bool actual = solution.isSameTree(node2, node4);
    EXPECT_EQ(expected, actual);
    delete node1;
    delete node2;
    delete node3;
    delete node4;
}

TEST(Solution, IsSameTree3) {
    Solution solution;
    TreeNode *node1 = new TreeNode(2);
    TreeNode *node2 = new TreeNode(1);
    TreeNode *node3 = new TreeNode(1, node1, node2);
    TreeNode *node4 = new TreeNode(1);
    TreeNode *node5 = new TreeNode(2);
    TreeNode *node6 = new TreeNode(1, node4, node5);
    bool expected = false;
    bool actual = solution.isSameTree(node3, node6);
    EXPECT_EQ(expected, actual);
    delete node1;
    delete node2;
    delete node3;
    delete node4;
    delete node5;
    delete node6;
}

TEST(Solution, IsSameTree4) {
    Solution solution;
    TreeNode *node1 = new TreeNode(1);
    TreeNode *node2 = new TreeNode(1, node1, nullptr);
    TreeNode *node3 = new TreeNode(1);
    TreeNode *node4 = new TreeNode(1, nullptr, node3);
    bool expected = false;
    bool actual = solution.isSameTree(node2, node4);
    EXPECT_EQ(expected, actual);
    delete node1;
    delete node2;
    delete node3;
    delete node4;
}