#include "tree_utils.hpp"
#include <gtest/gtest.h>
#include <initializer_list>
#include <optional>
#include <queue>
#include <string>

using namespace std;
using namespace TreeUtils;

class Codec {
  public:
    // Encodes a tree to a single string.
    string serialize(TreeNode *root) {
        string s;
        if (root == nullptr) {
            return s;
        }

        queue<TreeNode *> nodes;
        nodes.push(root);

        while (!nodes.empty()) {
            int levelSize = nodes.size();

            for (int i = 0; i < levelSize; i++) {
                TreeNode *current = nodes.front();
                nodes.pop();

                if (current != root) {
                    s += ',';
                }
                if (current != nullptr) {
                    s += to_string(current->val);
                    nodes.push(current->left);
                    nodes.push(current->right);
                } else {
                    s += 'x';
                }
            }
        }

        while (s.back() == 'x') {
            s.erase(s.length() - 2);
        }

        return s;
    }

    // Decodes your encoded data to tree.
    TreeNode *deserialize(string data) {
        auto start = data.begin();
        auto val = read(data, start);
        if (!val.has_value()) {
            return nullptr;
        }

        TreeNode *root = new TreeNode(val.value());
        queue<TreeNode *> nodes;
        nodes.push(root);

        while (start != data.end()) {
            TreeNode *current = nodes.front();
            nodes.pop();

            val = read(data, start);
            if (val.has_value()) {
                current->left = new TreeNode(val.value());
                nodes.push(current->left);
            }

            val = read(data, start);
            if (val.has_value()) {
                current->right = new TreeNode(val.value());
                nodes.push(current->right);
            }
        }

        return root;
    }

  private:
    optional<int> read(const string &data, string::iterator &start) {
        if (start == data.end()) {
            return nullopt;
        }

        if (*start == 'x') {
            start += 2;
            return nullopt;
        }

        auto end = start;
        while (end != data.end() && *end != ',') {
            end++;
        }

        string val(start, end);

        if (end == data.end()) {
            start = end;
        } else {
            start = end + 1;
        }

        return stoi(val);
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));

class Codec1Test : public ::testing::Test {
  protected:
    Codec ser;
    Codec deser;
};

TEST_F(Codec1Test, TestCase1) {
    initializer_list<optional<int>> values = {1, 2, 3, nullopt, nullopt, 4, 5};
    TreeNode *root = createTree(values);

    string actual = ser.serialize(root);
    string expected = "1,2,3,x,x,4,5";

    EXPECT_EQ(actual, expected);

    TreeNode *ans = deser.deserialize(actual);

    EXPECT_TRUE(compareTree(ans, values));

    deleteTree(root);
    deleteTree(ans);
}

TEST_F(Codec1Test, TestCase2) {
    initializer_list<optional<int>> values = {};
    TreeNode *root = createTree(values);

    string actual = ser.serialize(root);
    string expected = "";

    EXPECT_EQ(actual, expected);

    TreeNode *ans = deser.deserialize(actual);

    EXPECT_TRUE(compareTree(ans, values));

    deleteTree(root);
    deleteTree(ans);
}

TEST_F(Codec1Test, TestCase3) {
    initializer_list<optional<int>> values = {13,      nullopt, 26,
                                              nullopt, 33,      nullopt};
    TreeNode *root = createTree(values);

    string actual = ser.serialize(root);
    string expected = "13,x,26,x,33";

    EXPECT_EQ(actual, expected);

    TreeNode *ans = deser.deserialize(actual);

    EXPECT_TRUE(compareTree(ans, values));

    deleteTree(root);
    deleteTree(ans);
}