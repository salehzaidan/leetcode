#include "tree_utils.hpp"
#include <gtest/gtest.h>

using namespace std;
using namespace TreeUtils;

class Solution1 {
  public:
    int kthSmallest(TreeNode *root, int k) {
        int index = 1;
        int smallest = 0;
        traverse(root, k, index, smallest);
        return smallest;
    }

  private:
    void traverse(TreeNode *node, int k, int &index, int &smallest) {
        if (node == nullptr) {
            return;
        }

        traverse(node->left, k, index, smallest);

        if (k == index++) {
            smallest = node->val;
            return;
        }

        traverse(node->right, k, index, smallest);
    }
};

class Solution1Test : public ::testing::Test {
  protected:
    Solution1 solution;
};

TEST_F(Solution1Test, TestCase1) {
    TreeNode *root = createTree({3, 1, 4, nullopt, 2});
    int k = 1;

    int actual = solution.kthSmallest(root, k);
    int expected = 1;

    EXPECT_EQ(actual, expected);

    deleteTree(root);
}

TEST_F(Solution1Test, TestCase2) {
    TreeNode *root = createTree({5, 3, 6, 2, 4, nullopt, nullopt, 1});
    int k = 3;

    int actual = solution.kthSmallest(root, k);
    int expected = 3;

    EXPECT_EQ(actual, expected);

    deleteTree(root);
}