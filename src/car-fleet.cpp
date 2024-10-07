#include <algorithm>
#include <gtest/gtest.h>
#include <stack>
#include <vector>

using namespace std;

class Solution1 {
public:
  int carFleet(int target, const vector<int> &position,
               const vector<int> &speed) {
    vector<int> indices(position.size());
    for (int i = 0; i < indices.size(); i++) {
      indices[i] = i;
    }
    sort(indices.begin(), indices.end(),
         [&](int i, int j) { return position[i] > position[j]; });

    int fleet = 0;
    stack<double> times;
    for (const int &i : indices) {
      double current = (target - position[i]) / (double)speed[i];

      if (times.empty()) {
        times.push(current);
        fleet++;
        continue;
      }

      double front = times.top();
      if (current > front) {
        times.pop();
        times.push(current);
        fleet++;
      }
    }

    return fleet;
  }
};

TEST(Solution1, testCase1) {
  int target = 12;
  vector<int> position = {10, 8, 0, 5, 3};
  vector<int> speed = {2, 4, 1, 1, 3};

  Solution1 solution;
  EXPECT_EQ(solution.carFleet(target, position, speed), 3);
}

TEST(Solution1, testCase2) {
  int target = 10;
  vector<int> position = {3};
  vector<int> speed = {3};

  Solution1 solution;
  EXPECT_EQ(solution.carFleet(target, position, speed), 1);
}

TEST(Solution1, testCase3) {
  int target = 100;
  vector<int> position = {0, 2, 4};
  vector<int> speed = {4, 2, 1};

  Solution1 solution;
  EXPECT_EQ(solution.carFleet(target, position, speed), 1);
}

TEST(Solution1, testCase4) {
  int target = 10;
  vector<int> position = {6, 8};
  vector<int> speed = {3, 2};

  Solution1 solution;
  EXPECT_EQ(solution.carFleet(target, position, speed), 2);
}

TEST(Solution1, testCase5) {
  int target = 10;
  vector<int> position = {9, 8};
  vector<int> speed = {3, 2};

  Solution1 solution;
  EXPECT_EQ(solution.carFleet(target, position, speed), 2);
}