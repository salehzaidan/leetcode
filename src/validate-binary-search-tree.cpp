#include "tree_utils.hpp"
#include <gtest/gtest.h>

using namespace std;
using namespace TreeUtils;

class Solution1 {
  public:
    bool isValidBST(TreeNode *root) {
        TreeNode *prev = nullptr;
        return traverse(root, prev);
    }

  private:
    bool traverse(TreeNode *node, TreeNode *&prev) {
        if (node == nullptr) {
            return true;
        }

        bool left = traverse(node->left, prev);

        if (prev != nullptr && node->val <= prev->val) {
            return false;
        }
        prev = node;

        bool right = traverse(node->right, prev);

        return left && right;
    }
};

class Solution1Test : public ::testing::Test {
  protected:
    Solution1 solution;
};

TEST_F(Solution1Test, TestCase1) {
    TreeNode *root = createTree({2, 1, 3});

    bool actual = solution.isValidBST(root);
    bool expected = true;

    EXPECT_EQ(actual, expected);

    deleteTree(root);
}

TEST_F(Solution1Test, TestCase2) {
    TreeNode *root = createTree({5, 1, 4, nullopt, nullopt, 3, 6});

    bool actual = solution.isValidBST(root);
    bool expected = false;

    EXPECT_EQ(actual, expected);

    deleteTree(root);
}

TEST_F(Solution1Test, TestCase3) {
    TreeNode *root = createTree({2, 2, 2});

    bool actual = solution.isValidBST(root);
    bool expected = false;

    EXPECT_EQ(actual, expected);

    deleteTree(root);
}

TEST_F(Solution1Test, TestCase4) {
    TreeNode *root = createTree({5, 4, 6, nullopt, nullopt, 3, 7});

    bool actual = solution.isValidBST(root);
    bool expected = false;

    EXPECT_EQ(actual, expected);

    deleteTree(root);
}