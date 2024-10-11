#include "linked_list_utils.hpp"
#include <gtest/gtest.h>

using namespace std;
using namespace LinkedListUtils;

class Solution1 {
  public:
    ListNode *reverseList(ListNode *head) {
        ListNode *prev = nullptr;
        ListNode *next = nullptr;
        ListNode *current = head;

        while (current != nullptr) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }

        return prev;
    }
};

class Solution1Test : public ::testing::Test {
  protected:
    Solution1 solution;
};

TEST_F(Solution1Test, TestCase1) {
    ListNode *head = createList({1, 2, 3, 4, 5});

    ListNode *actual = solution.reverseList(head);

    EXPECT_TRUE(compareList(actual, {5, 4, 3, 2, 1}));

    deleteList(actual);
}

TEST_F(Solution1Test, TestCase2) {
    ListNode *head = createList({1, 2});

    ListNode *actual = solution.reverseList(head);

    EXPECT_TRUE(compareList(actual, {2, 1}));

    deleteList(actual);
}

TEST_F(Solution1Test, TestCase3) {
    ListNode *head = createList({});

    ListNode *actual = solution.reverseList(head);

    EXPECT_TRUE(compareList(actual, {}));

    deleteList(actual);
}

class Solution2 {
  public:
    ListNode *reverseList(ListNode *head) { return reverseNode(head, nullptr); }

  private:
    ListNode *reverseNode(ListNode *current, ListNode *prev) {
        if (current == nullptr) {
            return prev;
        }

        ListNode *next = current->next;
        current->next = prev;
        return reverseNode(next, current);
    }
};

class Solution2Test : public ::testing::Test {
  protected:
    Solution2 solution;
};

TEST_F(Solution2Test, TestCase1) {
    ListNode *head = createList({1, 2, 3, 4, 5});

    ListNode *actual = solution.reverseList(head);

    EXPECT_TRUE(compareList(actual, {5, 4, 3, 2, 1}));

    deleteList(actual);
}

TEST_F(Solution2Test, TestCase2) {
    ListNode *head = createList({1, 2});

    ListNode *actual = solution.reverseList(head);

    EXPECT_TRUE(compareList(actual, {2, 1}));

    deleteList(actual);
}

TEST_F(Solution2Test, TestCase3) {
    ListNode *head = createList({});

    ListNode *actual = solution.reverseList(head);

    EXPECT_TRUE(compareList(actual, {}));

    deleteList(actual);
}