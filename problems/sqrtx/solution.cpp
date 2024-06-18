#include <gtest/gtest.h>

using namespace std;

class Solution {
  public:
    int mySqrt(int x) {
        int i = 1;
        int j = x;

        while (i <= j) {
            long mid = i + (j - i) / 2;
            long square = mid * mid;

            if (square == x) {
                return mid;
            }

            if (square > x) {
                j = mid - 1;
            } else {
                i = mid + 1;
            }
        }

        return i - 1;
    }
};

TEST(Solution, MySqrt1) {
    Solution solution;
    int x = 4;
    int expected = 2;
    int actual = solution.mySqrt(x);
    EXPECT_EQ(expected, actual);
}

TEST(Solution, MySqrt2) {
    Solution solution;
    int x = 8;
    int expected = 2;
    int actual = solution.mySqrt(x);
    EXPECT_EQ(expected, actual);
}

TEST(Solution, MySqrt3) {
    Solution solution;
    int x = 15;
    int expected = 3;
    int actual = solution.mySqrt(x);
    EXPECT_EQ(expected, actual);
}

TEST(Solution, MySqrt4) {
    Solution solution;
    int x = 0;
    int expected = 0;
    int actual = solution.mySqrt(x);
    EXPECT_EQ(expected, actual);
}

TEST(Solution, MySqrt5) {
    Solution solution;
    int x = 2147395599;
    int expected = 46339;
    int actual = solution.mySqrt(x);
    EXPECT_EQ(expected, actual);
}

