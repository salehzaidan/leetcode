#include <gtest/gtest.h>
#include <limits>
#include <list>
#include <unordered_map>

using namespace std;

class LRUCache1 {
  public:
    LRUCache1(int capacity) {
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

TEST(LRUCache1, TestCase1) {
    LRUCache1 *obj = new LRUCache1(2);
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

class LRUCache2 {
  public:
    LRUCache2(int capacity) { _capacity = capacity; }

    int get(int key) {
        if (!_map.contains(key)) {
            return -1;
        }

        const auto entry = _map[key];
        auto it = entry.first;
        int value = entry.second;
        _list.erase(it);
        _list.push_front(key);
        _map[key] = {_list.begin(), value};

        return value;
    }

    void put(int key, int value) {
        if (_map.contains(key)) {
            auto &entry = _map[key];
            auto it = entry.first;
            entry.second = value;
            _list.erase(it);
            _list.push_front(key);
            _map[key] = {_list.begin(), value};
            return;
        }

        if (_map.size() == _capacity) {
            int lru = _list.back();
            _list.pop_back();
            _map.erase(lru);
        }

        _list.push_front(key);
        _map[key] = {_list.begin(), value};
    }

  private:
    int _capacity;
    list<int> _list;
    unordered_map<int, pair<list<int>::iterator, int>> _map;
};

TEST(LRUCache2, TestCase1) {
    LRUCache2 *obj = new LRUCache2(2);
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

TEST(LRUCache2, TestCase2) {
    LRUCache2 *obj = new LRUCache2(2);
    obj->put(2, 1);
    obj->put(2, 2);
    EXPECT_EQ(obj->get(2), 2);
    obj->put(1, 1);
    obj->put(4, 1);
    EXPECT_EQ(obj->get(2), -1);
    delete obj;
}

TEST(LRUCache2, TestCase3) {
    LRUCache2 *obj = new LRUCache2(2);
    EXPECT_EQ(obj->get(2), -1);
    obj->put(2, 6);
    EXPECT_EQ(obj->get(1), -1);
    obj->put(1, 5);
    obj->put(1, 2);
    EXPECT_EQ(obj->get(1), 2);
    EXPECT_EQ(obj->get(2), 6);
    delete obj;
}

TEST(LRUCache2, TestCase4) {
    LRUCache2 *obj = new LRUCache2(2);
    obj->put(2, 1);
    obj->put(1, 1);
    obj->put(2, 3);
    obj->put(4, 1);
    EXPECT_EQ(obj->get(1), -1);
    EXPECT_EQ(obj->get(2), 3);
    delete obj;
}