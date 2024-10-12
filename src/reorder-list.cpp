#include "linked_list_utils.hpp"
#include <gtest/gtest.h>
#include <stack>

using namespace std;
using namespace LinkedListUtils;

class Solution1 {
  public:
    void reorderList(ListNode *head) {
        stack<ListNode *> nodes;

        ListNode *current = head;
        while (current != nullptr) {
            nodes.push(current);
            current = current->next;
        }

        int length = nodes.size();
        current = head;
        ListNode *next = nullptr;
        for (int i = 0; i < length; i++) {
            if ((i & 1) == 0) {
                next = current->next;
                current->next = nodes.top();
                nodes.pop();
            } else {
                current->next = next;
            }
            current = current->next;
        }

        current->next = nullptr;
    }
};

class Solution1Test : public ::testing::Test {
  protected:
    Solution1 solution;
};

TEST_F(Solution1Test, TestCase1) {
    ListNode *head = createList({1, 2, 3, 4});

    solution.reorderList(head);

    EXPECT_TRUE(compareList(head, {1, 4, 2, 3}));

    deleteList(head);
}

TEST_F(Solution1Test, TestCase2) {
    ListNode *head = createList({1, 2, 3, 4, 5});

    solution.reorderList(head);

    EXPECT_TRUE(compareList(head, {1, 5, 2, 4, 3}));

    deleteList(head);
}