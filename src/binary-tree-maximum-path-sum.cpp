#include "tree_utils.hpp"
#include <gtest/gtest.h>
#include <limits>

using namespace std;
using namespace TreeUtils;

class Solution1 {
  public:
    int maxPathSum(TreeNode *root) {
        int maxSum = numeric_limits<int>::min();
        traverse(root, maxSum);
        return maxSum;
    }

  private:
    int traverse(TreeNode *node, int &maxSum) {
        if (node == nullptr) {
            return 0;
        }

        int left = max(0, traverse(node->left, maxSum));
        int right = max(0, traverse(node->right, maxSum));

        int sum = left + right + node->val;
        maxSum = max(maxSum, sum);

        return max(left, right) + node->val;
    }
};

class Solution1Test : public ::testing::Test {
  protected:
    Solution1 solution;
};

TEST_F(Solution1Test, TestCase1) {
    TreeNode *root = createTree({1, 2, 3});

    int actual = solution.maxPathSum(root);
    int expected = 6;

    EXPECT_EQ(actual, expected);

    deleteTree(root);
}

TEST_F(Solution1Test, TestCase2) {
    TreeNode *root = createTree({-10, 9, 20, nullopt, nullopt, 15, 7});

    int actual = solution.maxPathSum(root);
    int expected = 42;

    EXPECT_EQ(actual, expected);

    deleteTree(root);
}

TEST_F(Solution1Test, TestCase3) {
    TreeNode *root = createTree({-10, 9, 20, nullopt, nullopt, -15, -7});

    int actual = solution.maxPathSum(root);
    int expected = 20;

    EXPECT_EQ(actual, expected);

    deleteTree(root);
}