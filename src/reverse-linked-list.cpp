#include <gtest/gtest.h>
#include <initializer_list>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode *createList(initializer_list<int> values) {
    if (values.size() == 0) {
        return nullptr;
    }

    auto it = values.begin();
    ListNode *head = new ListNode(*it++);
    ListNode *current = head;

    while (it != values.end()) {
        current->next = new ListNode(*it++);
        current = current->next;
    }

    return head;
}

void deleteList(ListNode *head) {
    while (head != nullptr) {
        ListNode *temp = head;
        head = head->next;
        delete temp;
    }
}

bool compareList(ListNode *head, initializer_list<int> values) {
    auto it = values.begin();
    while (head != nullptr && it != values.end()) {
        if (head->val != *it) {
            return false;
        }

        head = head->next;
        it++;
    }

    return head == nullptr && it == values.end();
}

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