#include "tree_utils.hpp"
#include <gtest/gtest.h>
#include <optional>
#include <string>

using namespace TreeUtils;

TEST(TestTreeUtils, GeneralTree) {
    TreeNode *root = createTree({3, 9, 20, std::nullopt, std::nullopt, 15, 7});

    std::string actual = visualizeTree(root);
    std::string expected = "[3, 9, 20, null, null, 15, 7]";
    EXPECT_EQ(actual, expected);

    deleteTree(root);
}

TEST(TestTreeUtils, BalancedTree) {
    TreeNode *root = createTree({1, 2, 3, 4, 5, 6, 7});

    std::string actual = visualizeTree(root);
    std::string expected = "[1, 2, 3, 4, 5, 6, 7]";
    EXPECT_EQ(actual, expected);

    deleteTree(root);
}

TEST(TestTreeUtils, UnbalancedTree) {
    TreeNode *root = createTree({1, 2, std::nullopt, 3, std::nullopt, 4});

    std::string actual = visualizeTree(root);
    std::string expected = "[1, 2, null, 3, null, 4]";
    EXPECT_EQ(actual, expected);

    deleteTree(root);
}