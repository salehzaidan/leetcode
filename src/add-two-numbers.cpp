#include "linked_list_utils.hpp"
#include <gtest/gtest.h>

using namespace std;
using namespace LinkedListUtils;

class Solution1 {
  public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        ListNode *sentinel = new ListNode();
        ListNode *current = sentinel;
        int carry = 0;

        while (l1 != nullptr && l2 != nullptr) {
            int val = l1->val + l2->val + carry;
            current->next = new ListNode(val % 10);
            carry = val / 10;
            current = current->next;
            l1 = l1->next;
            l2 = l2->next;
        }

        while (l1 != nullptr) {
            int val = l1->val + carry;
            current->next = new ListNode(val % 10);
            carry = val / 10;
            current = current->next;
            l1 = l1->next;
        }

        while (l2 != nullptr) {
            int val = l2->val + carry;
            current->next = new ListNode(val % 10);
            carry = val / 10;
            current = current->next;
            l2 = l2->next;
        }

        if (carry != 0) {
            current->next = new ListNode(carry);
            current = current->next;
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
    ListNode *l1 = createList({2, 4, 3});
    ListNode *l2 = createList({5, 6, 4});

    ListNode *actual = solution.addTwoNumbers(l1, l2);

    EXPECT_TRUE(compareList(actual, {7, 0, 8}));

    deleteList(l1);
    deleteList(l2);
    deleteList(actual);
}

TEST_F(Solution1Test, TestCase2) {
    ListNode *l1 = createList({0});
    ListNode *l2 = createList({0});

    ListNode *actual = solution.addTwoNumbers(l1, l2);

    EXPECT_TRUE(compareList(actual, {0}));

    deleteList(l1);
    deleteList(l2);
    deleteList(actual);
}

TEST_F(Solution1Test, TestCase3) {
    ListNode *l1 = createList({9, 9, 9, 9, 9, 9, 9});
    ListNode *l2 = createList({9, 9, 9, 9});

    ListNode *actual = solution.addTwoNumbers(l1, l2);

    EXPECT_TRUE(compareList(actual, {8, 9, 9, 9, 0, 0, 0, 1}));

    deleteList(l1);
    deleteList(l2);
    deleteList(actual);
}
