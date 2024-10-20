#include "tree_utils.hpp"
#include <gtest/gtest.h>
#include <queue>
#include <vector>

using namespace std;
using namespace TreeUtils;

class Solution1 {
  public:
    vector<vector<int>> levelOrder(TreeNode *root) {
        vector<vector<int>> result;

        queue<TreeNode *> nodes;
        if (root != nullptr) {
            nodes.push(root);
        }

        while (!nodes.empty()) {
            vector<int> level;
            int levelSize = nodes.size();

            for (int i = 0; i < levelSize; i++) {
                TreeNode *current = nodes.front();
                nodes.pop();

                level.push_back(current->val);

                if (current->left != nullptr) {
                    nodes.push(current->left);
                }
                if (current->right != nullptr) {
                    nodes.push(current->right);
                }
            }

            result.push_back(level);
        }

        return result;
    }
};

class Solution1Test : public ::testing::Test {
  protected:
    Solution1 solution;
};

TEST_F(Solution1Test, TestCase1) {
    TreeNode *root = createTree({3, 9, 20, nullopt, nullopt, 15, 7});

    vector<vector<int>> actual = solution.levelOrder(root);
    vector<vector<int>> expected = {{3}, {9, 20}, {15, 7}};

    EXPECT_EQ(actual, expected);

    deleteTree(root);
}

TEST_F(Solution1Test, TestCase2) {
    TreeNode *root = createTree({1});

    vector<vector<int>> actual = solution.levelOrder(root);
    vector<vector<int>> expected = {{1}};

    EXPECT_EQ(actual, expected);

    deleteTree(root);
}

TEST_F(Solution1Test, TestCase3) {
    TreeNode *root = createTree({});

    vector<vector<int>> actual = solution.levelOrder(root);
    vector<vector<int>> expected = {};

    EXPECT_EQ(actual, expected);

    deleteTree(root);
}