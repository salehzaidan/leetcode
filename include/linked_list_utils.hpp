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

inline ListNode *createListCycle(std::initializer_list<int> values, int pos) {
    ListNode *head = createList(values);
    ListNode *current = head;

    ListNode *cycle = nullptr;
    int i = 0;
    while (current->next != nullptr) {
        if (i == pos) {
            cycle = current;
        }

        i++;
        current = current->next;
    }

    current->next = cycle;
    return head;
}

inline void deleteList(ListNode *head) {
    while (head != nullptr) {
        ListNode *temp = head;
        head = head->next;
        delete temp;
    }
}

inline void deleteListCycle(ListNode *head, int pos) {
    ListNode *cycle = nullptr;
    int i = 0;
    while (head != cycle) {
        if (i == pos) {
            cycle = head;
        }

        ListNode *temp = head;
        head = head->next;
        delete temp;
        i++;
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