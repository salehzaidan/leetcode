#include <gtest/gtest.h>

using namespace std;

class Solution {
  public:
    int add(int a, int b) { return a + b; }
};

TEST(Solution, Add) {
    Solution solution;
    int expected = 3;
    int actual = solution.add(1, 2);
    EXPECT_EQ(expected, actual);
}
