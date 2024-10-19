#include "tree_utils.hpp"
#include <gtest/gtest.h>

using namespace std;
using namespace TreeUtils;

class Solution1 {
  public:
    bool isSubtree(TreeNode *root, TreeNode *subRoot) {
        return traverse(root, subRoot);
    }

  private:
    bool traverse(TreeNode *node, TreeNode *subRoot) {
        if (node == nullptr) {
            return subRoot == nullptr;
        }

        bool self = isSameTree(node, subRoot);
        bool left = traverse(node->left, subRoot);
        bool right = traverse(node->right, subRoot);

        return self || left || right;
    }

    bool isSameTree(TreeNode *node1, TreeNode *node2) {
        if (node1 == nullptr || node2 == nullptr) {
            return node1 == nullptr && node2 == nullptr;
        }

        if (node1->val != node2->val) {
            return false;
        }

        bool left = isSameTree(node1->left, node2->left);
        bool right = isSameTree(node1->right, node2->right);

        return left && right;
    }
};

class Solution1Test : public ::testing::Test {
  protected:
    Solution1 solution;
};

TEST_F(Solution1Test, TestCase1) {
    TreeNode *root = createTree({3, 4, 5, 1, 2});
    TreeNode *subRoot = createTree({4, 1, 2});

    bool actual = solution.isSubtree(root, subRoot);
    bool expected = true;

    EXPECT_EQ(actual, expected);

    deleteTree(root);
    deleteTree(subRoot);
}

TEST_F(Solution1Test, TestCase2) {
    TreeNode *root =
        createTree({3, 4, 5, 1, 2, nullopt, nullopt, nullopt, nullopt, 0});
    TreeNode *subRoot = createTree({4, 1, 2});

    bool actual = solution.isSubtree(root, subRoot);
    bool expected = false;

    EXPECT_EQ(actual, expected);

    deleteTree(root);
    deleteTree(subRoot);
}

TEST_F(Solution1Test, TestCase3) {
    TreeNode *root = createTree({3, 4, 5, 1, 2});
    TreeNode *subRoot = createTree({3, 4, 5, 1, 2});

    bool actual = solution.isSubtree(root, subRoot);
    bool expected = true;

    EXPECT_EQ(actual, expected);

    deleteTree(root);
    deleteTree(subRoot);
}

TEST_F(Solution1Test, TestCase4) {
    TreeNode *root = createTree({1, nullopt, 1, nullopt, 1, nullopt, 1, nullopt,
                                 1, nullopt, 1, nullopt, 1, nullopt, 1, nullopt,
                                 1, nullopt, 1, nullopt, 1, 2});
    TreeNode *subRoot = createTree(
        {1, nullopt, 1, nullopt, 1, nullopt, 1, nullopt, 1, nullopt, 1, 2});

    bool actual = solution.isSubtree(root, subRoot);
    bool expected = true;

    EXPECT_EQ(actual, expected);

    deleteTree(root);
    deleteTree(subRoot);
}