#include "linked_list_utils.hpp"
#include <gtest/gtest.h>
#include <stack>

using namespace std;
using namespace LinkedListUtils;

class Solution1 {
  public:
    ListNode *removeNthFromEnd(ListNode *head, int n) {
        stack<ListNode *> nodes;

        ListNode *current = head;
        while (current != nullptr) {
            nodes.push(current);
            current = current->next;
        }

        for (int i = 0; i < n; i++) {
            nodes.pop();
        }

        if (nodes.empty()) {
            current = head->next;
            delete head;
            return current;
        }

        current = nodes.top();
        ListNode *target = current->next;
        current->next = target->next;
        delete target;

        return head;
    }
};

class Solution1Test : public ::testing::Test {
  protected:
    Solution1 solution;
};

TEST_F(Solution1Test, TestCase1) {
    ListNode *head = createList({1, 2, 3, 4, 5});
    int n = 2;

    ListNode *actual = solution.removeNthFromEnd(head, n);

    EXPECT_TRUE(compareList(actual, {1, 2, 3, 5}));

    deleteList(actual);
}

TEST_F(Solution1Test, TestCase2) {
    ListNode *head = createList({1});
    int n = 1;

    ListNode *actual = solution.removeNthFromEnd(head, n);

    EXPECT_TRUE(compareList(actual, {}));

    deleteList(actual);
}

TEST_F(Solution1Test, TestCase3) {
    ListNode *head = createList({1, 2});
    int n = 1;

    ListNode *actual = solution.removeNthFromEnd(head, n);

    EXPECT_TRUE(compareList(actual, {1}));

    deleteList(actual);
}

TEST_F(Solution1Test, TestCase4) {
    ListNode *head = createList({1, 2});
    int n = 2;

    ListNode *actual = solution.removeNthFromEnd(head, n);

    EXPECT_TRUE(compareList(actual, {2}));

    deleteList(actual);
}