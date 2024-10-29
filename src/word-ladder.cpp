#include <forward_list>
#include <gtest/gtest.h>
#include <queue>
#include <string>
#include <unordered_map>

using namespace std;

class Solution1 {
  public:
    int ladderLength(string beginWord, string endWord,
                     vector<string> &wordList) {
        unordered_map<string, forward_list<string>> adj;
        buildGraph(adj, wordList, beginWord);

        unordered_map<string, int> distance;
        distance[beginWord] = 1;

        queue<string> q;
        q.push(beginWord);

        while (!q.empty()) {
            string u = q.front();
            q.pop();

            for (string v : adj[u]) {
                if (!distance.contains(v)) {
                    distance[v] = distance[u] + 1;
                    q.push(v);
                    if (v == endWord) {
                        return distance[v];
                    }
                }
            }
        }

        return 0;
    }

  private:
    void buildGraph(unordered_map<string, forward_list<string>> &adj,
                    vector<string> wordList, const string &beginWord) {
        unordered_map<string, vector<string>> patternsMap;

        wordList.push_back(beginWord);

        for (const string &word : wordList) {
            for (int i = 0; i < word.length(); i++) {
                string pattern = word;
                pattern[i] = '*';
                patternsMap[pattern].push_back(word);
            }
        }

        for (const auto &[pattern, words] : patternsMap) {
            for (const string &word1 : words) {
                for (const string &word2 : words) {
                    if (word1 != word2) {
                        adj[word1].push_front(word2);
                    }
                }
            }
        }
    }
};

class Solution1Test : public ::testing::Test {
  protected:
    Solution1 solution;
};

TEST_F(Solution1Test, TestCase1) {
    string beginWord = "hit";
    string endWord = "cog";
    vector<string> wordList = {"hot", "dot", "dog", "lot", "log", "cog"};

    int actual = solution.ladderLength(beginWord, endWord, wordList);
    int expected = 5;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase2) {
    string beginWord = "hit";
    string endWord = "cog";
    vector<string> wordList = {"hot", "dot", "dog", "lot", "log"};

    int actual = solution.ladderLength(beginWord, endWord, wordList);
    int expected = 0;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase3) {
    string beginWord = "abc";
    string endWord = "xyz";
    vector<string> wordList = {"abx", "abz", "xbz", "xyz"};

    int actual = solution.ladderLength(beginWord, endWord, wordList);
    int expected = 4;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase4) {
    string beginWord = "hog";
    string endWord = "cog";
    vector<string> wordList = {"cog"};

    int actual = solution.ladderLength(beginWord, endWord, wordList);
    int expected = 2;

    EXPECT_EQ(actual, expected);
}