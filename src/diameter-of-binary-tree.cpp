#include "tree_utils.hpp"
#include <gtest/gtest.h>
#include <stack>
#include <unordered_map>

using namespace std;
using namespace TreeUtils;

class Solution1 {
  public:
    int diameterOfBinaryTree(TreeNode *root) {
        int diameter = 0;
        height(root, diameter);
        return diameter;
    }

  private:
    int height(TreeNode *node, int &diameter) {
        if (node == nullptr) {
            return -1;
        }

        int left = height(node->left, diameter);
        int right = height(node->right, diameter);

        diameter = max(diameter, left + right + 2);

        return max(left, right) + 1;
    }
};

class Solution1Test : public ::testing::Test {
  protected:
    Solution1 solution;
};

TEST_F(Solution1Test, TestCase1) {
    TreeNode *root = createTree({1, 2, 3, 4, 5});

    int actual = solution.diameterOfBinaryTree(root);
    int expected = 3;

    EXPECT_EQ(actual, expected);

    deleteTree(root);
}

TEST_F(Solution1Test, TestCase2) {
    TreeNode *root = createTree({1, 2});

    int actual = solution.diameterOfBinaryTree(root);
    int expected = 1;

    EXPECT_EQ(actual, expected);

    deleteTree(root);
}

TEST_F(Solution1Test, TestCase3) {
    TreeNode *root = createTree({1, 2, nullopt, 3, 4, 5, 6});

    int actual = solution.diameterOfBinaryTree(root);
    int expected = 3;

    EXPECT_EQ(actual, expected);

    deleteTree(root);
}

class Solution2 {
  public:
    int diameterOfBinaryTree(TreeNode *root) {
        int diameter = 0;
        stack<pair<TreeNode *, bool>> nodes;
        nodes.push({root, false});

        unordered_map<TreeNode *, int> heights;

        while (!nodes.empty()) {
            auto [current, visited] = nodes.top();
            nodes.pop();

            if (!visited) {
                nodes.push({current, true});
                if (current->right != nullptr) {
                    nodes.push({current->right, false});
                }
                if (current->left != nullptr) {
                    nodes.push({current->left, false});
                }
            } else {
                int left =
                    (current->left != nullptr) ? heights[current->left] : -1;
                int right =
                    (current->right != nullptr) ? heights[current->right] : -1;
                heights[current] = max(left, right) + 1;
                diameter = max(diameter, left + right + 2);
            }
        }

        return diameter;
    }
};

class Solution2Test : public ::testing::Test {
  protected:
    Solution2 solution;
};

TEST_F(Solution2Test, TestCase1) {
    TreeNode *root = createTree({1, 2, 3, 4, 5});

    int actual = solution.diameterOfBinaryTree(root);
    int expected = 3;

    EXPECT_EQ(actual, expected);

    deleteTree(root);
}

TEST_F(Solution2Test, TestCase2) {
    TreeNode *root = createTree({1, 2});

    int actual = solution.diameterOfBinaryTree(root);
    int expected = 1;

    EXPECT_EQ(actual, expected);

    deleteTree(root);
}

TEST_F(Solution2Test, TestCase3) {
    TreeNode *root = createTree({1, 2, nullopt, 3, 4, 5, 6});

    int actual = solution.diameterOfBinaryTree(root);
    int expected = 3;

    EXPECT_EQ(actual, expected);

    deleteTree(root);
}