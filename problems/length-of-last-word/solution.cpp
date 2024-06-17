#include <cctype>
#include <gtest/gtest.h>

using namespace std;

class Solution {
  public:
    int lengthOfLastWord(string s) {
        int len = 0;
        bool inside = !isspace(static_cast<unsigned char>(s.back()));

        for (auto it = s.rbegin(); it != s.rend(); it++) {
            bool space = isspace(static_cast<unsigned char>(*it));

            if (inside) {
                if (space) {
                    inside = false;
                    break;
                }

                len += 1;
            } else {
                if (!space) {
                    inside = true;
                    len += 1;
                }
            }
        }

        return len;
    }
};

TEST(Solution, LengthOfLastWord1) {
    Solution solution;
    int expected = 5;
    int actual = solution.lengthOfLastWord("Hello World");
    EXPECT_EQ(expected, actual);
}

TEST(Solution, LengthOfLastWord2) {
    Solution solution;
    int expected = 4;
    int actual = solution.lengthOfLastWord("   fly me   to   the moon  ");
    EXPECT_EQ(expected, actual);
}

TEST(Solution, LengthOfLastWord3) {
    Solution solution;
    int expected = 6;
    int actual = solution.lengthOfLastWord("luffy is still joyboy");
    EXPECT_EQ(expected, actual);
}

TEST(Solution, LengthOfLastWord4) {
    Solution solution;
    int expected = 1;
    int actual = solution.lengthOfLastWord("a");
    EXPECT_EQ(expected, actual);
}
