#include "tree_utils.hpp"
#include <gtest/gtest.h>
#include <stack>

using namespace std;
using namespace TreeUtils;

class Solution1 {
  public:
    TreeNode *invertTree(TreeNode *root) {
        invertNode(root);
        return root;
    }

  private:
    void invertNode(TreeNode *node) {
        if (node == nullptr) {
            return;
        }

        swap(node->left, node->right);

        invertNode(node->left);
        invertNode(node->right);
    }
};

class Solution1Test : public ::testing::Test {
  protected:
    Solution1 solution;
};

TEST_F(Solution1Test, TestCase1) {
    TreeNode *root = createTree({4, 2, 7, 1, 3, 6, 9});

    TreeNode *actual = solution.invertTree(root);

    EXPECT_TRUE(compareTree(actual, {4, 7, 2, 9, 6, 3, 1}));

    deleteTree(actual);
}

TEST_F(Solution1Test, TestCase2) {
    TreeNode *root = createTree({2, 1, 3});

    TreeNode *actual = solution.invertTree(root);

    EXPECT_TRUE(compareTree(actual, {2, 3, 1}));

    deleteTree(actual);
}

class Solution2 {
  public:
    TreeNode *invertTree(TreeNode *root) {
        stack<TreeNode *> nodes;
        nodes.push(root);

        while (!nodes.empty()) {
            TreeNode *current = nodes.top();
            nodes.pop();

            swap(current->left, current->right);

            if (current->right != nullptr) {
                nodes.push(current->right);
            }
            if (current->left != nullptr) {
                nodes.push(current->left);
            }
        }

        return root;
    }
};

class Solution2Test : public ::testing::Test {
  protected:
    Solution2 solution;
};

TEST_F(Solution2Test, TestCase1) {
    TreeNode *root = createTree({4, 2, 7, 1, 3, 6, 9});

    TreeNode *actual = solution.invertTree(root);

    EXPECT_TRUE(compareTree(actual, {4, 7, 2, 9, 6, 3, 1}));

    deleteTree(actual);
}

TEST_F(Solution2Test, TestCase2) {
    TreeNode *root = createTree({2, 1, 3});

    TreeNode *actual = solution.invertTree(root);

    EXPECT_TRUE(compareTree(actual, {2, 3, 1}));

    deleteTree(actual);
}