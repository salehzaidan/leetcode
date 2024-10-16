#include "linked_list_utils.hpp"
#include <gtest/gtest.h>

using namespace std;
using namespace LinkedListUtils;

class Solution1 {
  public:
    ListNode *reverseKGroup(ListNode *head, int k) {
        ListNode *current = head;
        ListNode *start = head;
        ListNode *end = nullptr;
        ListNode *last = nullptr;
        head = nullptr;
        int i = 1;
        while (current != nullptr) {
            if (i == k) {
                end = current->next;
                current = start;
                ListNode *prev = nullptr;
                ListNode *next = nullptr;
                while (current != end) {
                    next = current->next;
                    current->next = prev;
                    prev = current;
                    current = next;
                }

                if (head == nullptr) {
                    head = prev;
                }

                if (last != nullptr) {
                    last->next = prev;
                }
                last = start;

                if (current == nullptr) {
                    break;
                }

                start->next = current;
                start = current;
                i = 1;
            }

            current = current->next;
            i++;
        }

        return head;
    }
};

class Solution1Test : public ::testing::Test {
  protected:
    Solution1 solution;
};

TEST_F(Solution1Test, TestCase1) {
    ListNode *head = createList({1, 2, 3, 4, 5});
    int k = 2;

    ListNode *actual = solution.reverseKGroup(head, k);

    EXPECT_TRUE(compareList(actual, {2, 1, 4, 3, 5}));

    deleteList(actual);
}

TEST_F(Solution1Test, TestCase2) {
    ListNode *head = createList({1, 2, 3, 4, 5});
    int k = 3;

    ListNode *actual = solution.reverseKGroup(head, k);

    EXPECT_TRUE(compareList(actual, {3, 2, 1, 4, 5}));

    deleteList(actual);
}

TEST_F(Solution1Test, TestCase3) {
    ListNode *head = createList({1});
    int k = 1;

    ListNode *actual = solution.reverseKGroup(head, k);

    EXPECT_TRUE(compareList(actual, {1}));

    deleteList(actual);
}