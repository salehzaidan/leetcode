#include "linked_list_utils.hpp"
#include <algorithm>
#include <gtest/gtest.h>
#include <vector>

using namespace std;
using namespace LinkedListUtils;

class Solution1 {
  public:
    ListNode *mergeKLists(const vector<ListNode *> &lists) {
        ListNode *sentinel = new ListNode();
        ListNode *current = sentinel;

        auto nodesComp = [](const ListNode *a, const ListNode *b) {
            if (a == nullptr || b == nullptr) {
                return false;
            }
            return a->val < b->val;
        };

        vector<ListNode *> nodes;
        for (ListNode *list : lists) {
            if (list != nullptr) {
                nodes.push_back(list);
            }
        }

        while (!nodes.empty()) {
            auto it = min_element(nodes.begin(), nodes.end(), nodesComp);
            ListNode *&node = *it;
            if (node == nullptr) {
                break;
            }

            current->next = new ListNode(node->val);
            current = current->next;
            node = node->next;
            if (node == nullptr) {
                nodes.erase(it);
            }
        }

        ListNode *head = sentinel->next;
        delete sentinel;
        return head;
    }
};

class Solution1Test : public ::testing::Test {
  protected:
    Solution1 solution;
};

TEST_F(Solution1Test, TestCase1) {
    vector<ListNode *> lists = {
        createList({1, 4, 5}),
        createList({1, 3, 4}),
        createList({2, 6}),
    };

    ListNode *actual = solution.mergeKLists(lists);

    EXPECT_TRUE(compareList(actual, {1, 1, 2, 3, 4, 4, 5, 6}));

    for (ListNode *list : lists) {
        deleteList(list);
    }
    deleteList(actual);
}

TEST_F(Solution1Test, TestCase2) {
    vector<ListNode *> lists = {};

    ListNode *actual = solution.mergeKLists(lists);

    EXPECT_TRUE(compareList(actual, {}));

    for (ListNode *list : lists) {
        deleteList(list);
    }
    deleteList(actual);
}

TEST_F(Solution1Test, TestCase3) {
    vector<ListNode *> lists = {
        createList({}),
    };

    ListNode *actual = solution.mergeKLists(lists);

    EXPECT_TRUE(compareList(actual, {}));

    for (ListNode *list : lists) {
        deleteList(list);
    }
    deleteList(actual);
}