#include "tree_utils.hpp"
#include <gtest/gtest.h>
#include <unordered_map>
#include <vector>

using namespace std;
using namespace TreeUtils;

class Solution1 {
  public:
    TreeNode *buildTree(const vector<int> &preorder,
                        const vector<int> &inorder) {
        unordered_map<int, int> indices;
        for (int i = 0; i < inorder.size(); i++) {
            indices[inorder[i]] = i;
        }

        return buildSubTree(preorder, 0, preorder.size(), inorder, 0,
                            inorder.size(), indices);
    }

  private:
    TreeNode *buildSubTree(const vector<int> &preorder, int preStart,
                           int preEnd, const vector<int> &inorder, int inStart,
                           int inEnd, const unordered_map<int, int> &indices) {
        if (preStart == preEnd) {
            return nullptr;
        }

        TreeNode *subRoot = new TreeNode(preorder[preStart]);

        int pos = indices.at(subRoot->val);
        int leftSize = pos - inStart;
        int rightSize = inEnd - pos - 1;

        TreeNode *left =
            buildSubTree(preorder, preStart + 1, preStart + 1 + leftSize,
                         inorder, inStart, pos, indices);
        subRoot->left = left;

        TreeNode *right = buildSubTree(preorder, preStart + 1 + leftSize,
                                       preStart + 1 + leftSize + rightSize,
                                       inorder, pos + 1, inEnd, indices);
        subRoot->right = right;

        return subRoot;
    }
};

class Solution1Test : public ::testing::Test {
  protected:
    Solution1 solution;
};

TEST_F(Solution1Test, TestCase1) {
    vector<int> preorder = {3, 9, 20, 15, 7};
    vector<int> inorder = {9, 3, 15, 20, 7};

    TreeNode *actual = solution.buildTree(preorder, inorder);

    EXPECT_TRUE(compareTree(actual, {3, 9, 20, nullopt, nullopt, 15, 7}));

    deleteTree(actual);
}

TEST_F(Solution1Test, TestCase2) {
    vector<int> preorder = {-1};
    vector<int> inorder = {-1};

    TreeNode *actual = solution.buildTree(preorder, inorder);

    EXPECT_TRUE(compareTree(actual, {-1}));

    deleteTree(actual);
}

TEST_F(Solution1Test, TestCase3) {
    vector<int> preorder = {4, 2, 1, 3, 6, 5, 7};
    vector<int> inorder = {1, 2, 3, 4, 5, 6, 7};

    TreeNode *actual = solution.buildTree(preorder, inorder);

    EXPECT_TRUE(compareTree(actual, {4, 2, 6, 1, 3, 5, 7}));

    deleteTree(actual);
}