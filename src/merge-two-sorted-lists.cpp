#include "linked_list_utils.hpp"
#include <gtest/gtest.h>

using namespace std;
using namespace LinkedListUtils;

class Solution1 {
  public:
    ListNode *mergeTwoLists(ListNode *list1, ListNode *list2) {
        ListNode *sentinel = new ListNode();
        ListNode *current = sentinel;

        while (list1 != nullptr && list2 != nullptr) {
            if (list1->val <= list2->val) {
                current->next = list1;
                list1 = list1->next;
            } else {
                current->next = list2;
                list2 = list2->next;
            }
            current = current->next;
        }

        if (list1 != nullptr) {
            current->next = list1;
        } else {
            current->next = list2;
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
    ListNode *list1 = createList({1, 2, 4});
    ListNode *list2 = createList({1, 3, 4});

    ListNode *actual = solution.mergeTwoLists(list1, list2);

    EXPECT_TRUE(compareList(actual, {1, 1, 2, 3, 4, 4}));

    deleteList(actual);
}

TEST_F(Solution1Test, TestCase2) {
    ListNode *list1 = createList({});
    ListNode *list2 = createList({});

    ListNode *actual = solution.mergeTwoLists(list1, list2);

    EXPECT_TRUE(compareList(actual, {}));

    deleteList(actual);
}

TEST_F(Solution1Test, TestCase3) {
    ListNode *list1 = createList({});
    ListNode *list2 = createList({0});

    ListNode *actual = solution.mergeTwoLists(list1, list2);

    EXPECT_TRUE(compareList(actual, {0}));

    deleteList(actual);
}