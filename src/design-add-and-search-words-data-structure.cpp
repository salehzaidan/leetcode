#include <gtest/gtest.h>

using namespace std;

class WordDictionary1 {
  public:
    WordDictionary1() { root = new Node(); }

    ~WordDictionary1() { deleteNode(root); }

    void addWord(const string &word) {
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
        return searchSubstring(word.begin(), word.end(), root);
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

    bool searchSubstring(string::const_iterator begin,
                         string::const_iterator end, Node *current) {
        for (auto it = begin; it != end; it++) {
            char val = *it;
            if (val == '.') {
                for (Node *next : current->children) {
                    if (next != nullptr && searchSubstring(it + 1, end, next)) {
                        return true;
                    }
                }

                return false;
            }

            int index = val - 'a';
            Node *next = current->children[index];

            if (next == nullptr) {
                return false;
            }

            current = next;
        }

        return current->terminal;
    }

    void deleteNode(Node *node) {
        for (Node *next : node->children) {
            if (next != nullptr) {
                deleteNode(next);
            }
        }
        delete node;
    }
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */

class WordDictionary1Test : public ::testing::Test {
  protected:
    WordDictionary1 obj;
};

TEST_F(WordDictionary1Test, TestCase1) {
    obj.addWord("bad");
    obj.addWord("dad");
    obj.addWord("mad");
    EXPECT_FALSE(obj.search("pad"));
    EXPECT_TRUE(obj.search("bad"));
    EXPECT_TRUE(obj.search(".ad"));
    EXPECT_TRUE(obj.search("b.."));
}

TEST_F(WordDictionary1Test, TestCase2) {
    obj.addWord("apple");
    obj.addWord("app");
    EXPECT_TRUE(obj.search("app.e"));
    EXPECT_TRUE(obj.search("appl."));
    EXPECT_TRUE(obj.search(".pp.e"));
}