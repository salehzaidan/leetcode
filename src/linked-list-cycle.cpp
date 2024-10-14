#include "linked_list_utils.hpp"
#include <gtest/gtest.h>

using namespace std;
using namespace LinkedListUtils;

class Solution1 {
  public:
    bool hasCycle(ListNode *head) {
        ListNode *slow = head;
        ListNode *fast = head;

        while (slow != nullptr && fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;

            if (slow == fast) {
                return true;
            }
        }

        return false;
    }
};

class Solution1Test : public ::testing::Test {
  protected:
    Solution1 solution;
};

TEST_F(Solution1Test, TestCase1) {
    int pos = 1;
    ListNode *head = createListCycle({3, 2, 0, -4}, pos);

    bool actual = solution.hasCycle(head);
    bool expected = true;

    EXPECT_EQ(actual, expected);

    deleteListCycle(head, pos);
}

TEST_F(Solution1Test, TestCase2) {
    int pos = 0;
    ListNode *head = createListCycle({1, 2}, pos);

    bool actual = solution.hasCycle(head);
    bool expected = true;

    EXPECT_EQ(actual, expected);

    deleteListCycle(head, pos);
}

TEST_F(Solution1Test, TestCase3) {
    int pos = -1;
    ListNode *head = createListCycle({1}, pos);

    bool actual = solution.hasCycle(head);
    bool expected = false;

    EXPECT_EQ(actual, expected);

    deleteListCycle(head, pos);
}

TEST_F(Solution1Test, TestCase4) {
    int pos = -1;
    ListNode *head = createListCycle({1, 2}, pos);

    bool actual = solution.hasCycle(head);
    bool expected = false;

    EXPECT_EQ(actual, expected);

    deleteListCycle(head, pos);
}