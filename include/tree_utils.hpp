#ifndef TREE_UTILS_HPP
#define TREE_UTILS_HPP

#include <initializer_list>
#include <optional>
#include <queue>
#include <string>

namespace TreeUtils {

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right)
        : val(x), left(left), right(right) {}
};

inline TreeNode *createTree(std::initializer_list<std::optional<int>> values) {
    if (values.size() == 0 || !values.begin()->has_value()) {
        return nullptr;
    }

    auto it = values.begin();
    TreeNode *root = new TreeNode(it->value());
    it++;

    std::queue<TreeNode *> nodes;
    nodes.push(root);

    while (it != values.end()) {
        TreeNode *current = nodes.front();
        nodes.pop();

        if (it != values.end() && it->has_value()) {
            current->left = new TreeNode(it->value());
            nodes.push(current->left);
        }
        it++;

        if (it != values.end() && it->has_value()) {
            current->right = new TreeNode(it->value());
            nodes.push(current->right);
        }
        if (it != values.end()) {
            it++;
        }
    }

    return root;
}

inline std::string visualizeTree(TreeNode *root) {
    if (root == nullptr)
        return "[null]";

    std::string result = "[";
    std::queue<TreeNode *> nodes;
    nodes.push(root);

    bool endLevel = false;

    while (!nodes.empty()) {
        TreeNode *current = nodes.front();
        nodes.pop();

        if (current != nullptr) {
            result += std::to_string(current->val) + ", ";
            nodes.push(current->left);
            nodes.push(current->right);
        } else {
            result += "null, ";
            endLevel = true;
        }

        if (endLevel && nodes.empty()) {
            while (result.size() >= 6 &&
                   result.substr(result.size() - 6) == "null, ") {
                result.erase(result.size() - 6);
            }
            while (result.size() >= 2 &&
                   result.substr(result.size() - 2) == ", ") {
                result.erase(result.size() - 2);
            }
        }
    }

    result += "]";
    return result;
}

inline void deleteTree(TreeNode *root) {
    if (root != nullptr) {
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
    }
}

inline bool compareTree(TreeNode *root,
                        std::initializer_list<std::optional<int>> values) {
    std::queue<TreeNode *> nodes;
    auto it = values.begin();

    nodes.push(root);

    while (!nodes.empty() && it != values.end()) {
        TreeNode *current = nodes.front();
        nodes.pop();

        if (current != nullptr) {
            if (*it == std::nullopt || current->val != **it) {
                return false;
            }

            nodes.push(current->left);
            nodes.push(current->right);
        } else {
            if (*it != std::nullopt) {
                return false;
            }
        }
        it++;
    }

    return it == values.end();
}

} // namespace TreeUtils

#endif // TREE_UTILS_HPP