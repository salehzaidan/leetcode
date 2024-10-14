#include <gtest/gtest.h>
#include <limits>
#include <unordered_map>

using namespace std;

class LRUCache {
  public:
    LRUCache(int capacity) {
        _capacity = capacity;
        _nextRank = 0;
    }

    int get(int key) {
        if (!_map.contains(key)) {
            return -1;
        }

        Entry &entry = _map.at(key);
        entry.rank = _nextRank++;
        return entry.value;
    }

    void put(int key, int value) {
        if (_map.contains(key)) {
            Entry &entry = _map.at(key);
            entry.rank = _nextRank++;
            entry.value = value;
            return;
        }

        if (_map.size() == _capacity) {
            int lowestRankKey = -1;
            int lowestRank = numeric_limits<int>::max();
            for (auto &[key, entry] : _map) {
                if (entry.rank < lowestRank) {
                    lowestRank = entry.rank;
                    lowestRankKey = key;
                }
            }

            _map.erase(lowestRankKey);
        }

        _map.insert({key, Entry{.value = value, .rank = _nextRank++}});
    }

  private:
    int _capacity;
    int _nextRank;

    struct Entry {
        int value;
        int rank;
    };
    unordered_map<int, Entry> _map;
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

TEST(LRUCache, TestCase1) {
    LRUCache *obj = new LRUCache(2);
    obj->put(1, 1);
    obj->put(2, 2);
    EXPECT_EQ(obj->get(1), 1);
    obj->put(3, 3);
    EXPECT_EQ(obj->get(2), -1);
    obj->put(4, 4);
    EXPECT_EQ(obj->get(1), -1);
    EXPECT_EQ(obj->get(3), 3);
    EXPECT_EQ(obj->get(4), 4);
    delete obj;
}
