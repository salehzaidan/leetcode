#include "tree_utils.hpp"
#include <gtest/gtest.h>
#include <queue>
#include <vector>

using namespace std;
using namespace TreeUtils;

class Solution1 {
  public:
    vector<int> rightSideView(TreeNode *root) {
        vector<int> result;

        queue<TreeNode *> nodes;
        if (root != nullptr) {
            nodes.push(root);
        }

        while (!nodes.empty()) {
            int levelSize = nodes.size();

            for (int i = 0; i < levelSize; i++) {
                TreeNode *current = nodes.front();
                nodes.pop();

                if (i == levelSize - 1) {
                    result.push_back(current->val);
                }

                if (current->left != nullptr) {
                    nodes.push(current->left);
                }
                if (current->right != nullptr) {
                    nodes.push(current->right);
                }
            }
        }

        return result;
    }
};

class Solution1Test : public ::testing::Test {
  protected:
    Solution1 solution;
};

TEST_F(Solution1Test, TestCase1) {
    TreeNode *root = createTree({1, 2, 3, nullopt, 5, nullopt, 4});

    vector<int> actual = solution.rightSideView(root);
    vector<int> expected = {1, 3, 4};

    EXPECT_EQ(actual, expected);

    deleteTree(root);
}

TEST_F(Solution1Test, TestCase2) {
    TreeNode *root = createTree({1, nullopt, 3});

    vector<int> actual = solution.rightSideView(root);
    vector<int> expected = {1, 3};

    EXPECT_EQ(actual, expected);

    deleteTree(root);
}

TEST_F(Solution1Test, TestCase3) {
    TreeNode *root = createTree({});

    vector<int> actual = solution.rightSideView(root);
    vector<int> expected = {};

    EXPECT_EQ(actual, expected);

    deleteTree(root);
}

TEST_F(Solution1Test, TestCase4) {
    TreeNode *root = createTree({6, 2, 8, 0, 4, 7, 9, nullopt, nullopt, 3, 5});

    vector<int> actual = solution.rightSideView(root);
    vector<int> expected = {6, 8, 9, 5};

    EXPECT_EQ(actual, expected);

    deleteTree(root);
}