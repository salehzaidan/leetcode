#include <gtest/gtest.h>

#include "listnode.hpp"

using namespace std;

class Solution {
  public:
    ListNode *deleteDuplicates(ListNode *head) {
        if (head == nullptr) {
            return nullptr;
        }

        auto prev = head;
        auto now = head->next;

        while (now != nullptr) {
            if (prev->val == now->val) {
                prev->next = now->next;
            } else {
                prev = prev->next;
            }

            now = now->next;
        }

        return head;
    }
};

TEST(Solution, DeleteDuplicates1) {
    Solution solution;
    ListNode *expected = new ListNode{1, 2};
    ListNode *actual = solution.deleteDuplicates(new ListNode{1, 1, 2});
    EXPECT_EQ(expected->toString(), actual->toString());
}

TEST(Solution, DeleteDuplicates2) {
    Solution solution;
    ListNode *expected = new ListNode{1, 2, 3};
    ListNode *actual = solution.deleteDuplicates(new ListNode{1, 1, 2, 3, 3});
    EXPECT_EQ(expected->toString(), actual->toString());
}

TEST(Solution, DeleteDuplicates3) {
    Solution solution;
    ListNode *expected = nullptr;
    ListNode *actual = solution.deleteDuplicates(nullptr);
    EXPECT_EQ(expected->toString(), actual->toString());
}

TEST(Solution, DeleteDuplicates4) {
    Solution solution;
    ListNode *expected = new ListNode{1};
    ListNode *actual = solution.deleteDuplicates(new ListNode{1, 1, 1});
    EXPECT_EQ(expected->toString(), actual->toString());
}
