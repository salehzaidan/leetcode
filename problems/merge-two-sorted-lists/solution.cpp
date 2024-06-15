#include <gtest/gtest.h>
#include <initializer_list>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
    ListNode(initializer_list<int> values) : val(0), next(nullptr) {
        if (values.size() == 0) {
            return;
        }

        auto iter = values.begin();
        val = *iter;
        ListNode *now = this;
        iter++;

        while (iter != values.end()) {
            now->next = new ListNode(*iter);
            now = now->next;
            iter++;
        }
    }

    string print() {
        string s;
        ListNode *now = this;

        while (now != nullptr) {
            if (now != this) {
                s += "->";
            }
            s += to_string(now->val);
            now = now->next;
        }

        return s;
    }
};

class Solution {
  public:
    ListNode *mergeTwoLists(ListNode *list1, ListNode *list2) {
        auto tmp = new ListNode();
        auto now = tmp;

        while (list1 != nullptr && list2 != nullptr) {
            if (list1->val < list2->val) {
                now->next = list1;
                list1 = list1->next;
            } else {
                now->next = list2;
                list2 = list2->next;
            }
            now = now->next;
        }

        if (list1 != nullptr) {
            now->next = list1;
        } else {
            now->next = list2;
        }

        return tmp->next;
    }
};

TEST(Solution, MergeTwoLists1) {
    Solution solution;
    ListNode *expected = new ListNode{1, 1, 2, 3, 4, 4};
    ListNode *actual =
        solution.mergeTwoLists(new ListNode{1, 2, 4}, new ListNode{1, 3, 4});
    EXPECT_EQ(expected->print(), actual->print());
}

TEST(Solution, MergeTwoLists2) {
    Solution solution;
    ListNode *expected = nullptr;
    ListNode *actual = solution.mergeTwoLists(nullptr, nullptr);
    EXPECT_EQ(expected->print(), actual->print());
}

TEST(Solution, MergeTwoLists3) {
    Solution solution;
    ListNode *expected = new ListNode(0);
    ListNode *actual = solution.mergeTwoLists(nullptr, new ListNode{0});
    EXPECT_EQ(expected->print(), actual->print());
}
