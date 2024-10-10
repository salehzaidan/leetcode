#include <gtest/gtest.h>
#include <string>
#include <unordered_map>

using namespace std;

class TimeMap {
  public:
    TimeMap() {}

    void set(string key, string value, int timestamp) {
        _map[key].push_back(TimeValue{value, timestamp});
    }

    string get(string key, int timestamp) {
        const vector<TimeValue> &v = _map[key];
        int best = -1;

        int left = 0;
        int right = v.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (v[mid].timestamp == timestamp) {
                return v[mid].value;
            } else if (v[mid].timestamp < timestamp) {
                best = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        return best == -1 ? "" : v[best].value;
    }

  private:
    struct TimeValue {
        string value;
        int timestamp;
    };

    unordered_map<string, vector<TimeValue>> _map;
};

/**
 * Your TimeMap object will be instantiated and called as such:
 * TimeMap* obj = new TimeMap();
 * obj->set(key,value,timestamp);
 * string param_2 = obj->get(key,timestamp);
 */

TEST(TimeMap, TestCase1) {
    TimeMap *obj = new TimeMap();
    obj->set("foo", "bar", 1);
    EXPECT_EQ(obj->get("foo", 1), "bar");
    EXPECT_EQ(obj->get("foo", 3), "bar");
    obj->set("foo", "bar2", 4);
    EXPECT_EQ(obj->get("foo", 4), "bar2");
    EXPECT_EQ(obj->get("foo", 5), "bar2");
    delete obj;
}

TEST(TimeMap, TestCase2) {
    TimeMap *obj = new TimeMap();
    obj->set("foo", "bar", 1);
    EXPECT_EQ(obj->get("foo", 1), "bar");
    obj->set("foo", "bar2", 4);
    EXPECT_EQ(obj->get("foo", 2), "bar");
    EXPECT_EQ(obj->get("foo", 5), "bar2");
    delete obj;
}