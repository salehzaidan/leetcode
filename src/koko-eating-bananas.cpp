#include <algorithm>
#include <gtest/gtest.h>

using namespace std;

class Solution1 {
  public:
    int minEatingSpeed(const vector<int> &piles, int h) {
        int left = 1;
        int right = *max_element(piles.begin(), piles.end());
        int minSpeed = right;

        while (left <= right) {
            int speed = left + (right - left) / 2;
            long long time = 0;
            for (const int &pile : piles) {
                time += (pile + speed - 1) / speed;
            }

            if (time <= h) {
                minSpeed = min(minSpeed, speed);
                right = speed - 1;
            } else {
                left = speed + 1;
            }
        }

        return minSpeed;
    }
};

class Solution1Test : public ::testing::Test {
  protected:
    Solution1 solution;
};

TEST_F(Solution1Test, TestCase1) {
    vector<int> piles = {3, 6, 7, 11};
    int h = 8;

    int actual = solution.minEatingSpeed(piles, h);
    int expected = 4;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase2) {
    vector<int> piles = {30, 11, 23, 4, 20};
    int h = 5;

    int actual = solution.minEatingSpeed(piles, h);
    int expected = 30;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase3) {
    vector<int> piles = {30, 11, 23, 4, 20};
    int h = 6;

    int actual = solution.minEatingSpeed(piles, h);
    int expected = 23;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase4) {
    vector<int> piles = {1, 2};
    int h = 6;

    int actual = solution.minEatingSpeed(piles, h);
    int expected = 1;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase5) {
    vector<int> piles = {805306368, 805306368, 805306368};
    int h = 1000000000;

    int actual = solution.minEatingSpeed(piles, h);
    int expected = 3;

    EXPECT_EQ(actual, expected);
}