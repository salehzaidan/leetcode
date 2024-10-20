#include "tree_utils.hpp"
#include <gtest/gtest.h>
#include <limits>
#include <optional>
#include <unordered_map>

using namespace std;
using namespace TreeUtils;

class Solution1 {
  public:
    int goodNodes(TreeNode *root) {
        unordered_map<TreeNode *, TreeNode *> parents;
        traverseParent(root, parents);

        unordered_map<TreeNode *, int> maximum;
        int count = 0;
        traverseGood(root, parents, maximum, count);
        return count;
    }

  private:
    void traverseParent(TreeNode *node,
                        unordered_map<TreeNode *, TreeNode *> &parents) {
        if (node->left != nullptr) {
            parents[node->left] = node;
            traverseParent(node->left, parents);
        }
        if (node->right != nullptr) {
            parents[node->right] = node;
            traverseParent(node->right, parents);
        }
    }

    void traverseGood(TreeNode *node,
                      unordered_map<TreeNode *, TreeNode *> &parents,
                      unordered_map<TreeNode *, int> &maximum, int &count) {
        if (node == nullptr) {
            return;
        }

        TreeNode *parent = parents[node];
        if (!maximum.contains(parent)) {
            maximum[parent] = numeric_limits<int>::min();
        }

        if (node->val >= maximum[parent]) {
            maximum[node] = node->val;
            count++;
        } else {
            maximum[node] = maximum[parent];
        }

        traverseGood(node->left, parents, maximum, count);
        traverseGood(node->right, parents, maximum, count);
    }
};

class Solution1Test : public ::testing::Test {
  protected:
    Solution1 solution;
};

TEST_F(Solution1Test, TestCase1) {
    TreeNode *root = createTree({3, 1, 4, 3, nullopt, 1, 5});

    int actual = solution.goodNodes(root);
    int expected = 4;

    EXPECT_EQ(actual, expected);

    deleteTree(root);
}

TEST_F(Solution1Test, TestCase2) {
    TreeNode *root = createTree({3, 3, nullopt, 4, 2});

    int actual = solution.goodNodes(root);
    int expected = 3;

    EXPECT_EQ(actual, expected);

    deleteTree(root);
}

TEST_F(Solution1Test, TestCase3) {
    TreeNode *root = createTree({1});

    int actual = solution.goodNodes(root);
    int expected = 1;

    EXPECT_EQ(actual, expected);

    deleteTree(root);
}

TEST_F(Solution1Test, TestCase4) {
    TreeNode *root = createTree({2, nullopt, 4, 10, 8, nullopt, nullopt, 4});

    int actual = solution.goodNodes(root);
    int expected = 4;

    EXPECT_EQ(actual, expected);

    deleteTree(root);
}

TEST_F(Solution1Test, TestCase5) {
    TreeNode *root = createTree({9, nullopt, 3, 6});

    int actual = solution.goodNodes(root);
    int expected = 1;

    EXPECT_EQ(actual, expected);

    deleteTree(root);
}