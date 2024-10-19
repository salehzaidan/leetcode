#include "tree_utils.hpp"
#include <gtest/gtest.h>
#include <stack>

using namespace std;
using namespace TreeUtils;

class Solution1 {
  public:
    bool isSameTree(TreeNode *p, TreeNode *q) { return traverse(p, q); }

  private:
    bool traverse(TreeNode *node1, TreeNode *node2) {
        if (node1 == nullptr || node2 == nullptr) {
            return node1 == nullptr && node2 == nullptr;
        }

        if (node1->val != node2->val) {
            return false;
        }

        bool left = traverse(node1->left, node2->left);
        bool right = traverse(node1->right, node2->right);

        return left && right;
    }
};

class Solution1Test : public ::testing::Test {
  protected:
    Solution1 solution;
};

TEST_F(Solution1Test, TestCase1) {
    TreeNode *p = createTree({1, 2, 3});
    TreeNode *q = createTree({1, 2, 3});

    bool actual = solution.isSameTree(p, q);
    bool expected = true;

    EXPECT_EQ(actual, expected);

    deleteTree(p);
    deleteTree(q);
}

TEST_F(Solution1Test, TestCase2) {
    TreeNode *p = createTree({1, 2});
    TreeNode *q = createTree({1, nullopt, 2});

    bool actual = solution.isSameTree(p, q);
    bool expected = false;

    EXPECT_EQ(actual, expected);

    deleteTree(p);
    deleteTree(q);
}

TEST_F(Solution1Test, TestCase3) {
    TreeNode *p = createTree({1, 2, 1});
    TreeNode *q = createTree({1, 1, 2});

    bool actual = solution.isSameTree(p, q);
    bool expected = false;

    EXPECT_EQ(actual, expected);

    deleteTree(p);
    deleteTree(q);
}

TEST_F(Solution1Test, TestCase4) {
    TreeNode *p = createTree({2, nullopt, 4});
    TreeNode *q = createTree({2, 3, 4});

    bool actual = solution.isSameTree(p, q);
    bool expected = false;

    EXPECT_EQ(actual, expected);

    deleteTree(p);
    deleteTree(q);
}

class Solution2 {
  public:
    bool isSameTree(TreeNode *p, TreeNode *q) {
        stack<pair<TreeNode *, TreeNode *>> nodes;
        nodes.push({p, q});

        while (!nodes.empty()) {
            auto [current1, current2] = nodes.top();
            nodes.pop();

            if (current1 == nullptr && current2 == nullptr) {
                continue;
            }

            if (current1 == nullptr || current2 == nullptr) {
                return false;
            }

            if (current1->val != current2->val) {
                return false;
            }

            nodes.push({current1->right, current2->right});
            nodes.push({current1->left, current2->left});
        }

        return true;
    }
};

class Solution2Test : public ::testing::Test {
  protected:
    Solution2 solution;
};

TEST_F(Solution2Test, TestCase1) {
    TreeNode *p = createTree({1, 2, 3});
    TreeNode *q = createTree({1, 2, 3});

    bool actual = solution.isSameTree(p, q);
    bool expected = true;

    EXPECT_EQ(actual, expected);

    deleteTree(p);
    deleteTree(q);
}

TEST_F(Solution2Test, TestCase2) {
    TreeNode *p = createTree({1, 2});
    TreeNode *q = createTree({1, nullopt, 2});

    bool actual = solution.isSameTree(p, q);
    bool expected = false;

    EXPECT_EQ(actual, expected);

    deleteTree(p);
    deleteTree(q);
}

TEST_F(Solution2Test, TestCase3) {
    TreeNode *p = createTree({1, 2, 1});
    TreeNode *q = createTree({1, 1, 2});

    bool actual = solution.isSameTree(p, q);
    bool expected = false;

    EXPECT_EQ(actual, expected);

    deleteTree(p);
    deleteTree(q);
}

TEST_F(Solution2Test, TestCase4) {
    TreeNode *p = createTree({2, nullopt, 4});
    TreeNode *q = createTree({2, 3, 4});

    bool actual = solution.isSameTree(p, q);
    bool expected = false;

    EXPECT_EQ(actual, expected);

    deleteTree(p);
    deleteTree(q);
}