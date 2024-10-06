#include <forward_list>
#include <gtest/gtest.h>
#include <optional>
#include <vector>

using namespace std;

class MinStack {
public:
  MinStack() {}

  void push(int val) {
    _actual.push_front(val);

    if (_min.empty() || val < *_min.front()) {
      _min.push_front(&_actual.front());
    }
  }

  void pop() {
    int *val = &_actual.front();
    if (_min.front() == val) {
      _min.pop_front();
    }

    _actual.pop_front();
  }

  int top() { return _actual.front(); }

  int getMin() { return *_min.front(); }

private:
  forward_list<int> _actual;
  forward_list<int *> _min;
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */

vector<optional<int>> applyOperations(const vector<string> &operations,
                                      const vector<vector<int>> &params) {
  vector<optional<int>> out;

  MinStack *obj;
  for (int i = 0; i < operations.size(); i++) {
    const string &operation = operations[i];
    const vector<int> &param = params[i];

    if (operation == "MinStack") {
      obj = new MinStack();
      out.push_back({});
    } else if (operation == "push") {
      obj->push(param[0]);
      out.push_back({});
    } else if (operation == "pop") {
      obj->pop();
      out.push_back({});
    } else if (operation == "top") {
      int value = obj->top();
      out.push_back(value);
    } else if (operation == "getMin") {
      int value = obj->getMin();
      out.push_back(value);
    }
  }
  delete obj;

  return out;
}

TEST(Solution1, testCase1) {
  vector<string> operations = {"MinStack", "push", "push", "push",
                               "getMin",   "pop",  "top",  "getMin"};
  vector<vector<int>> params = {{}, {-2}, {0}, {-3}, {}, {}, {}, {}};

  vector<optional<int>> expected = {{}, {}, {}, {}, -3, {}, 0, -2};

  EXPECT_EQ(applyOperations(operations, params), expected);
}
