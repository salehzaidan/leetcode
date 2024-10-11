#ifndef LINKED_LIST_UTILS_HPP
#define LINKED_LIST_UTILS_HPP

#include <initializer_list>

namespace LinkedListUtils {

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

inline ListNode *createList(std::initializer_list<int> values) {
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

inline void deleteList(ListNode *head) {
    while (head != nullptr) {
        ListNode *temp = head;
        head = head->next;
        delete temp;
    }
}

inline bool compareList(ListNode *head, std::initializer_list<int> values) {
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

} // namespace LinkedListUtils

#endif // LINKED_LIST_UTILS_HPP