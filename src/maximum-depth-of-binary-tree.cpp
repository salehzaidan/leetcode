#include "tree_utils.hpp"
#include <gtest/gtest.h>
#include <stack>

using namespace std;
using namespace TreeUtils;

class Solution1 {
  public:
    int maxDepth(TreeNode *root) {
        if (root == nullptr) {
            return 0;
        }

        int left = maxDepth(root->left);
        int right = maxDepth(root->right);

        return max(left, right) + 1;
    }
};

class Solution1Test : public ::testing::Test {
  protected:
    Solution1 solution;
};

TEST_F(Solution1Test, TestCase1) {
    TreeNode *root = createTree({3, 9, 20, nullopt, nullopt, 15, 7});

    int actual = solution.maxDepth(root);
    int expected = 3;

    EXPECT_EQ(actual, expected);

    deleteTree(root);
}

TEST_F(Solution1Test, TestCase2) {
    TreeNode *root = createTree({1, nullopt, 2});

    int actual = solution.maxDepth(root);
    int expected = 2;

    EXPECT_EQ(actual, expected);

    deleteTree(root);
}

class Solution2 {
  public:
    int maxDepth(TreeNode *root) {
        stack<pair<TreeNode *, int>> nodes;
        nodes.push({root, 0});

        int maximumDepth = 0;

        while (!nodes.empty()) {
            TreeNode *node = nodes.top().first;
            int depth = nodes.top().second;
            nodes.pop();

            depth++;
            maximumDepth = max(maximumDepth, depth);

            if (node->right != nullptr) {
                nodes.push({node->right, depth});
            }
            if (node->left != nullptr) {
                nodes.push({node->left, depth});
            }
        }

        return maximumDepth;
    }
};

class Solution2Test : public ::testing::Test {
  protected:
    Solution2 solution;
};

TEST_F(Solution2Test, TestCase1) {
    TreeNode *root = createTree({3, 9, 20, nullopt, nullopt, 15, 7});

    int actual = solution.maxDepth(root);
    int expected = 3;

    EXPECT_EQ(actual, expected);

    deleteTree(root);
}

TEST_F(Solution2Test, TestCase2) {
    TreeNode *root = createTree({1, nullopt, 2});

    int actual = solution.maxDepth(root);
    int expected = 2;

    EXPECT_EQ(actual, expected);

    deleteTree(root);
}