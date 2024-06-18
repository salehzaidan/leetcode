#pragma once

#include <initializer_list>
#include <string>

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
    ListNode(std::initializer_list<int> values) : val(0), next(nullptr) {
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

    std::string print() {
        std::string s;
        ListNode *now = this;

        while (now != nullptr) {
            if (now != this) {
                s += "->";
            }
            s += std::to_string(now->val);
            now = now->next;
        }

        return s;
    }
};
