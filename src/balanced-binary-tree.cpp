#include "tree_utils.hpp"
#include <cstdlib>
#include <gtest/gtest.h>
#include <stack>
#include <unordered_map>

using namespace std;
using namespace TreeUtils;

class Solution1 {
  public:
    bool isBalanced(TreeNode *root) {
        auto [_, balanced] = traverse(root);
        return balanced;
    }

  private:
    pair<int, bool> traverse(TreeNode *node) {
        if (node == nullptr) {
            return {-1, true};
        }

        auto [leftHeight, leftBalanced] = traverse(node->left);
        auto [rightHeight, rightBalanced] = traverse(node->right);

        int height = max(leftHeight, rightHeight) + 1;
        bool balanced =
            abs(leftHeight - rightHeight) <= 1 && leftBalanced && rightBalanced;

        return {height, balanced};
    }
};

class Solution1Test : public ::testing::Test {
  protected:
    Solution1 solution;
};

TEST_F(Solution1Test, TestCase1) {
    TreeNode *root = createTree({3, 9, 20, nullopt, nullopt, 15, 7});

    bool actual = solution.isBalanced(root);
    bool expected = true;

    EXPECT_EQ(actual, expected);

    deleteTree(root);
}

TEST_F(Solution1Test, TestCase2) {
    TreeNode *root = createTree({1, 2, 2, 3, 3, nullopt, nullopt, 4, 4});

    bool actual = solution.isBalanced(root);
    bool expected = false;

    EXPECT_EQ(actual, expected);

    deleteTree(root);
}

TEST_F(Solution1Test, TestCase3) {
    TreeNode *root = createTree({});

    bool actual = solution.isBalanced(root);
    bool expected = true;

    EXPECT_EQ(actual, expected);

    deleteTree(root);
}

TEST_F(Solution1Test, TestCase4) {
    TreeNode *root =
        createTree({1, 2, 2, 3, nullopt, nullopt, 3, 4, nullopt, nullopt, 4});

    bool actual = solution.isBalanced(root);
    bool expected = false;

    EXPECT_EQ(actual, expected);

    deleteTree(root);
}

class Solution2 {
  public:
    bool isBalanced(TreeNode *root) {
        if (root == nullptr) {
            return true;
        }

        unordered_map<TreeNode *, int> heights;

        stack<pair<TreeNode *, bool>> nodes;
        nodes.push({root, false});

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
                    (current->left == nullptr) ? -1 : heights[current->left];
                int right =
                    (current->right == nullptr) ? -1 : heights[current->right];

                if (abs(left - right) > 1) {
                    return false;
                }

                heights[current] = max(left, right) + 1;
            }
        }

        return true;
    }
};

class Solution2Test : public ::testing::Test {
  protected:
    Solution2 solution;
};

TEST_F(Solution2Test, TestCase1) {
    TreeNode *root = createTree({3, 9, 20, nullopt, nullopt, 15, 7});

    bool actual = solution.isBalanced(root);
    bool expected = true;

    EXPECT_EQ(actual, expected);

    deleteTree(root);
}

TEST_F(Solution2Test, TestCase2) {
    TreeNode *root = createTree({1, 2, 2, 3, 3, nullopt, nullopt, 4, 4});

    bool actual = solution.isBalanced(root);
    bool expected = false;

    EXPECT_EQ(actual, expected);

    deleteTree(root);
}

TEST_F(Solution2Test, TestCase3) {
    TreeNode *root = createTree({});

    bool actual = solution.isBalanced(root);
    bool expected = true;

    EXPECT_EQ(actual, expected);

    deleteTree(root);
}

TEST_F(Solution2Test, TestCase4) {
    TreeNode *root =
        createTree({1, 2, 2, 3, nullopt, nullopt, 3, 4, nullopt, nullopt, 4});

    bool actual = solution.isBalanced(root);
    bool expected = false;

    EXPECT_EQ(actual, expected);

    deleteTree(root);
}