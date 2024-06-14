#include <gtest/gtest.h>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
  public:
    int romanToInt(string s) {
        unordered_map<char, int> values = {
            {'I', 1},   {'V', 5},   {'X', 10},   {'L', 50},
            {'C', 100}, {'D', 500}, {'M', 1000},
        };
        int value = 0;

        for (size_t i = 0; i < s.size() - 1; i++) {
            auto now = values.at(s.at(i));
            auto next = values.at(s.at(i + 1));

            if (next > now) {
                value -= now;
            } else {
                value += now;
            }
        }
        value += values.at(s.back());

        return value;
    }
};

TEST(Solution, RomanToInt1) {
    Solution solution;
    int expected = 3;
    int actual = solution.romanToInt("III");
    EXPECT_EQ(expected, actual);
}

TEST(Solution, RomanToInt2) {
    Solution solution;
    int expected = 58;
    int actual = solution.romanToInt("LVIII");
    EXPECT_EQ(expected, actual);
}

TEST(Solution, RomanToInt3) {
    Solution solution;
    int expected = 1994;
    int actual = solution.romanToInt("MCMXCIV");
    EXPECT_EQ(expected, actual);
}
