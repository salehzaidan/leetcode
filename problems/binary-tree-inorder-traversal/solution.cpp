#include <gtest/gtest.h>
#include <stack>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right)
        : val(x), left(left), right(right) {}
};

class Solution1 {
  public:
    vector<int> inorderTraversal(TreeNode *root) {
        vector<int> values;
        traverse(root, values);
        return values;
    }

  private:
    void traverse(TreeNode *node, vector<int> &values) {
        if (node == nullptr) {
            return;
        }

        traverse(node->left, values);
        values.push_back(node->val);
        traverse(node->right, values);
    }
};

TEST(Solution1, InorderTraversal1) {
    Solution1 solution;
    TreeNode *node1 = new TreeNode(3);
    TreeNode *node2 = new TreeNode(2, node1, nullptr);
    TreeNode *node3 = new TreeNode(1, nullptr, node2);
    vector<int> expected{1, 3, 2};
    vector<int> actual = solution.inorderTraversal(node3);
    EXPECT_EQ(expected, actual);
    delete node1;
    delete node2;
    delete node3;
}

TEST(Solution1, InorderTraversal2) {
    Solution1 solution;
    TreeNode *node = nullptr;
    vector<int> expected{};
    vector<int> actual = solution.inorderTraversal(node);
    EXPECT_EQ(expected, actual);
}

TEST(Solution1, InorderTraversal3) {
    Solution1 solution;
    TreeNode *node = new TreeNode(1);
    vector<int> expected{1};
    vector<int> actual = solution.inorderTraversal(node);
    EXPECT_EQ(expected, actual);
    delete node;
}

TEST(Solution1, InorderTraversal4) {
    Solution1 solution;
    TreeNode *node1 = new TreeNode(4);
    TreeNode *node2 = new TreeNode(5);
    TreeNode *node3 = new TreeNode(2, node1, node2);
    TreeNode *node4 = new TreeNode(3);
    TreeNode *node5 = new TreeNode(1, node3, node4);
    vector<int> expected{4, 2, 5, 1, 3};
    vector<int> actual = solution.inorderTraversal(node5);
    EXPECT_EQ(expected, actual);
    delete node1;
    delete node2;
    delete node3;
    delete node4;
    delete node5;
}

class Solution2 {
  public:
    vector<int> inorderTraversal(TreeNode *root) {
        vector<int> values;
        stack<TreeNode *> st;

        auto node = root;
        while (node != nullptr || !st.empty()) {
            while (node != nullptr) {
                st.push(node);
                node = node->left;
            }

            node = st.top();
            st.pop();
            values.push_back(node->val);
            node = node->right;
        }

        return values;
    }
};

TEST(Solution2, InorderTraversal1) {
    Solution2 solution;
    TreeNode *node1 = new TreeNode(3);
    TreeNode *node2 = new TreeNode(2, node1, nullptr);
    TreeNode *node3 = new TreeNode(1, nullptr, node2);
    vector<int> expected{1, 3, 2};
    vector<int> actual = solution.inorderTraversal(node3);
    EXPECT_EQ(expected, actual);
    delete node1;
    delete node2;
    delete node3;
}

TEST(Solution2, InorderTraversal2) {
    Solution2 solution;
    TreeNode *node = nullptr;
    vector<int> expected{};
    vector<int> actual = solution.inorderTraversal(node);
    EXPECT_EQ(expected, actual);
}

TEST(Solution2, InorderTraversal3) {
    Solution2 solution;
    TreeNode *node = new TreeNode(1);
    vector<int> expected{1};
    vector<int> actual = solution.inorderTraversal(node);
    EXPECT_EQ(expected, actual);
    delete node;
}

TEST(Solution2, InorderTraversal4) {
    Solution2 solution;
    TreeNode *node1 = new TreeNode(4);
    TreeNode *node2 = new TreeNode(5);
    TreeNode *node3 = new TreeNode(2, node1, node2);
    TreeNode *node4 = new TreeNode(3);
    TreeNode *node5 = new TreeNode(1, node3, node4);
    vector<int> expected{4, 2, 5, 1, 3};
    vector<int> actual = solution.inorderTraversal(node5);
    EXPECT_EQ(expected, actual);
    delete node1;
    delete node2;
    delete node3;
    delete node4;
    delete node5;
}
