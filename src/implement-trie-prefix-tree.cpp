#include <array>
#include <gtest/gtest.h>

using namespace std;

class Trie1 {
  public:
    Trie1() { root = new Node(); }

    ~Trie1() { deleteNode(root); }

    void insert(const string &word) {
        Node *current = root;

        for (const char &val : word) {
            int index = val - 'a';
            Node *next = current->children[index];

            if (next != nullptr) {
                current = next;
            } else {
                current->children[index] = new Node(val);
                current = current->children[index];
            }
        }

        current->terminal = true;
    }

    bool search(const string &word) {
        Node *current = root;

        for (const char &val : word) {
            int index = val - 'a';
            Node *next = current->children[index];

            if (next == nullptr) {
                return false;
            }

            current = next;
        }

        return current->terminal;
    }

    bool startsWith(const string &prefix) {
        Node *current = root;

        for (const char &val : prefix) {
            int index = val - 'a';
            Node *next = current->children[index];

            if (next == nullptr) {
                return false;
            }

            current = next;
        }

        return true;
    }

  private:
    static constexpr int ALPHABET_SIZE = 26;

    struct Node {
        char val;
        array<Node *, ALPHABET_SIZE> children;
        bool terminal;

        Node() : val('\0'), children(), terminal() {}
        Node(char val) : val(val), children(), terminal() {}
    };

    Node *root;

    void deleteNode(Node *node) {
        for (Node *next : node->children) {
            if (next != nullptr) {
                deleteNode(next);
            }
        }
        delete node;
    }
};

class Trie1Test : public ::testing::Test {
  protected:
    Trie1 obj;
};

TEST_F(Trie1Test, TestCase1) {
    obj.insert("apple");
    EXPECT_TRUE(obj.search("apple"));
    EXPECT_FALSE(obj.search("app"));
    EXPECT_TRUE(obj.startsWith("app"));
    obj.insert("app");
    EXPECT_TRUE(obj.search("app"));
}

TEST_F(Trie1Test, TestCase2) {
    EXPECT_FALSE(obj.search(""));
    EXPECT_TRUE(obj.startsWith(""));
}

TEST_F(Trie1Test, TestCase3) {
    obj.insert("bat");
    obj.insert("batter");
    EXPECT_TRUE(obj.search("bat"));
    EXPECT_TRUE(obj.search("batter"));
    EXPECT_FALSE(obj.search("batterer"));
    EXPECT_TRUE(obj.startsWith("bat"));
    EXPECT_TRUE(obj.startsWith("batte"));
    EXPECT_FALSE(obj.startsWith("batters"));
}

TEST_F(Trie1Test, TestCase4) {
    obj.insert("cat");
    obj.insert("car");
    obj.insert("cart");
    obj.insert("dog");
    EXPECT_TRUE(obj.search("cat"));
    EXPECT_TRUE(obj.search("car"));
    EXPECT_TRUE(obj.search("cart"));
    EXPECT_TRUE(obj.search("dog"));
    EXPECT_FALSE(obj.search("catty"));
    EXPECT_TRUE(obj.startsWith("ca"));
    EXPECT_TRUE(obj.startsWith("do"));
    EXPECT_FALSE(obj.startsWith("doodle"));
}

class Trie2 {
  public:
    Trie2() { root = new Node(); }

    ~Trie2() { deleteNode(root); }

    void insert(const string &word) {
        Node *current = root;

        for (const char &val : word) {
            Node *next = current->leftChild;
            bool found = false;

            while (next != nullptr) {
                if (next->val == val) {
                    found = true;
                    break;
                }
                next = next->rightSibling;
            }

            if (found) {
                current = next;
            } else {
                Node *temp = new Node(val);
                temp->rightSibling = current->leftChild;
                current->leftChild = temp;
                current = current->leftChild;
            }
        }

        current->terminal = true;
    }

    bool search(const string &word) {
        Node *current = root;

        for (const char &val : word) {
            Node *next = current->leftChild;
            bool found = false;

            while (next != nullptr) {
                if (next->val == val) {
                    found = true;
                    break;
                }
                next = next->rightSibling;
            }

            if (!found) {
                return false;
            }

            current = next;
        }

        return current->terminal;
    }

    bool startsWith(const string &prefix) {
        Node *current = root;

        for (const char &val : prefix) {
            Node *next = current->leftChild;
            bool found = false;

            while (next != nullptr) {
                if (next->val == val) {
                    found = true;
                    break;
                }
                next = next->rightSibling;
            }

            if (!found) {
                return false;
            }

            current = next;
        }

        return true;
    }

  private:
    struct Node {
        char val;
        Node *leftChild;
        Node *rightSibling;
        bool terminal;

        Node() : val('\0'), leftChild(), rightSibling(), terminal() {}
        Node(char val) : val(val), leftChild(), rightSibling(), terminal() {}
    };

    Node *root;

    void deleteNode(Node *node) {
        Node *next = node->leftChild;
        while (next != nullptr) {
            Node *temp = next->rightSibling;
            deleteNode(next);
            next = temp;
        }
        delete node;
    }
};

class Trie2Test : public ::testing::Test {
  protected:
    Trie2 obj;
};

TEST_F(Trie2Test, TestCase1) {
    obj.insert("apple");
    EXPECT_TRUE(obj.search("apple"));
    EXPECT_FALSE(obj.search("app"));
    EXPECT_TRUE(obj.startsWith("app"));
    obj.insert("app");
    EXPECT_TRUE(obj.search("app"));
}

TEST_F(Trie2Test, TestCase2) {
    EXPECT_FALSE(obj.search(""));
    EXPECT_TRUE(obj.startsWith(""));
}

TEST_F(Trie2Test, TestCase3) {
    obj.insert("bat");
    obj.insert("batter");
    EXPECT_TRUE(obj.search("bat"));
    EXPECT_TRUE(obj.search("batter"));
    EXPECT_FALSE(obj.search("batterer"));
    EXPECT_TRUE(obj.startsWith("bat"));
    EXPECT_TRUE(obj.startsWith("batte"));
    EXPECT_FALSE(obj.startsWith("batters"));
}

TEST_F(Trie2Test, TestCase4) {
    obj.insert("cat");
    obj.insert("car");
    obj.insert("cart");
    obj.insert("dog");
    EXPECT_TRUE(obj.search("cat"));
    EXPECT_TRUE(obj.search("car"));
    EXPECT_TRUE(obj.search("cart"));
    EXPECT_TRUE(obj.search("dog"));
    EXPECT_FALSE(obj.search("catty"));
    EXPECT_TRUE(obj.startsWith("ca"));
    EXPECT_TRUE(obj.startsWith("do"));
    EXPECT_FALSE(obj.startsWith("doodle"));
}