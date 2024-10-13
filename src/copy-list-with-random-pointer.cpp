#include <algorithm>
#include <gtest/gtest.h>
#include <initializer_list>

using namespace std;

class Node {
  public:
    int val;
    Node *next;
    Node *random;

    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

Node *createList(std::initializer_list<pair<int, optional<int>>> values) {
    if (values.size() == 0) {
        return nullptr;
    }

    vector<Node *> nodes(values.size());
    for (auto it = values.begin(); it != values.end(); it++) {
        auto i = it - values.begin();
        nodes[i] = new Node(it->first);
    }
    for (auto it = values.begin(); it != values.end(); it++) {
        auto i = it - values.begin();
        if (i != nodes.size() - 1) {
            nodes[i]->next = nodes[i + 1];
        }
        if (it->second.has_value()) {
            nodes[i]->random = nodes[it->second.value()];
        }
    }

    return nodes.front();
}

void deleteList(Node *head) {
    while (head != nullptr) {
        Node *temp = head;
        head = head->next;
        delete temp;
    }
}

bool compareList(Node *head,
                 std::initializer_list<pair<int, optional<int>>> values) {
    vector<Node *> nodes;

    Node *current = head;
    while (current != nullptr) {
        nodes.push_back(current);
        current = current->next;
    }

    auto it = values.begin();
    while (head != nullptr && it != values.end()) {
        if (head->val != it->first) {
            return false;
        }

        if (it->second.has_value() &&
            head->random != nodes[it->second.value()]) {
            return false;
        }

        head = head->next;
        it++;
    }

    return head == nullptr && it == values.end();
}

class Solution1 {
  public:
    Node *copyRandomList(Node *head) {
        if (head == nullptr) {
            return nullptr;
        }

        vector<Node *> originals;
        vector<int> randoms;

        Node *current = head;
        while (current != nullptr) {
            originals.push_back(current);
            current = current->next;
        }

        for (const Node *node : originals) {
            if (node->random != nullptr) {
                auto it =
                    find(originals.begin(), originals.end(), node->random);
                randoms.push_back(it - originals.begin());
            } else {
                randoms.push_back(-1);
            }
        }

        vector<Node *> copies(originals.size());

        for (int i = 0; i < copies.size(); i++) {
            const Node *original = originals[i];
            copies[i] = new Node(original->val);
        }

        for (int i = 0; i < copies.size(); i++) {
            Node *copy = copies[i];
            if (i != copies.size() - 1) {
                copy->next = copies[i + 1];
            }
            if (randoms[i] != -1) {
                copy->random = copies[randoms[i]];
            }
        }

        return copies.front();
    }
};

class Solution1Test : public ::testing::Test {
  protected:
    Solution1 solution;
};

TEST_F(Solution1Test, TestCase1) {
    initializer_list<pair<int, optional<int>>> values = {
        {7, {}}, {13, 0}, {11, 4}, {10, 2}, {1, 0}};

    Node *head = createList(values);

    Node *actual = solution.copyRandomList(head);

    EXPECT_TRUE(compareList(actual, values));

    deleteList(head);
    deleteList(actual);
}

TEST_F(Solution1Test, TestCase2) {
    initializer_list<pair<int, optional<int>>> values = {{1, 1}, {2, 1}};

    Node *head = createList(values);

    Node *actual = solution.copyRandomList(head);

    EXPECT_TRUE(compareList(actual, values));

    deleteList(head);
    deleteList(actual);
}

TEST_F(Solution1Test, TestCase3) {
    initializer_list<pair<int, optional<int>>> values = {
        {3, {}}, {3, 0}, {3, {}}};

    Node *head = createList(values);

    Node *actual = solution.copyRandomList(head);

    EXPECT_TRUE(compareList(actual, values));

    deleteList(head);
    deleteList(actual);
}