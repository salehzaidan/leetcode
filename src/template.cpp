#include <gtest/gtest.h>

using namespace std;

class Solution1 {
  public:
    int add(int a, int b) { return a + b; }
};

class Solution1Test : public ::testing::Test {
  protected:
    Solution1 solution;
};

TEST_F(Solution1Test, TestCase1) {
    int a = 1;
    int b = 2;

    int actual = solution.add(a, b);
    int expected = 3;

    EXPECT_EQ(actual, expected);
}