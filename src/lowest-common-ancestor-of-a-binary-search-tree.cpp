#include "tree_utils.hpp"
#include <gtest/gtest.h>
#include <queue>

using namespace std;
using namespace TreeUtils;

class Solution1 {
  public:
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
        queue<TreeNode *> ancestors1 = collectAncestors(root, p->val);
        queue<TreeNode *> ancestors2 = collectAncestors(root, q->val);
        TreeNode *lca = ancestors1.front();

        while (!ancestors1.empty() && !ancestors2.empty()) {
            if (ancestors1.front() != ancestors2.front()) {
                return lca;
            }

            lca = ancestors1.front();
            ancestors1.pop();
            ancestors2.pop();
        }

        return lca;
    }

  private:
    queue<TreeNode *> collectAncestors(TreeNode *node, int val) {
        queue<TreeNode *> ancestors;

        while (node != nullptr && val != node->val) {
            ancestors.push(node);
            if (val < node->val) {
                node = node->left;
            } else {
                node = node->right;
            }
        }

        if (node != nullptr) {
            ancestors.push(node);
        }

        return ancestors;
    }
};

class Solution1Test : public ::testing::Test {
  protected:
    Solution1 solution;
};

TEST_F(Solution1Test, TestCase1) {
    TreeNode *root = createTree({6, 2, 8, 0, 4, 7, 9, nullopt, nullopt, 3, 5});
    TreeNode *p = root->left;
    TreeNode *q = root->right;

    TreeNode *actual = solution.lowestCommonAncestor(root, p, q);
    TreeNode *expected = root;

    EXPECT_EQ(actual, expected);

    deleteTree(root);
}

TEST_F(Solution1Test, TestCase2) {
    TreeNode *root = createTree({6, 2, 8, 0, 4, 7, 9, nullopt, nullopt, 3, 5});
    TreeNode *p = root->left;
    TreeNode *q = root->left->right;

    TreeNode *actual = solution.lowestCommonAncestor(root, p, q);
    TreeNode *expected = root->left;

    EXPECT_EQ(actual, expected);

    deleteTree(root);
}

TEST_F(Solution1Test, TestCase3) {
    TreeNode *root = createTree({2, 1});
    TreeNode *p = root;
    TreeNode *q = root->left;

    TreeNode *actual = solution.lowestCommonAncestor(root, p, q);
    TreeNode *expected = root;

    EXPECT_EQ(actual, expected);

    deleteTree(root);
}

TEST_F(Solution1Test, TestCase4) {
    TreeNode *root = createTree({6, 2, 8, 0, 4, 7, 9, nullopt, nullopt, 3, 5});
    TreeNode *p = root->left->left;
    TreeNode *q = root->left->right->right;

    TreeNode *actual = solution.lowestCommonAncestor(root, p, q);
    TreeNode *expected = root->left;

    EXPECT_EQ(actual, expected);

    deleteTree(root);
}