#include <gtest/gtest.h>
#include <unordered_map>

using namespace std;

class Solution1 {
  public:
    string minWindow(string s, string t) {
        unordered_map<char, int> windowFreq;
        unordered_map<char, int> refFreq;
        for (const char &ch : t) {
            windowFreq[ch] = 0;
            refFreq[ch]++;
        }

        int minLeft = -1;
        int minRight = -1;

        int left = 0;
        for (int right = 0; right < s.length(); right++) {
            windowFreq[s[right]]++;

            while (isSubstring(windowFreq, refFreq)) {
                if (minLeft == -1 || minRight == -1 ||
                    right - left < minRight - minLeft) {
                    minLeft = left;
                    minRight = right;
                }

                windowFreq[s[left]]--;
                left++;
            }
        }

        if (minLeft == -1 || minRight == -1) {
            return "";
        }
        return s.substr(minLeft, minRight - minLeft + 1);
    }

  private:
    bool isSubstring(const unordered_map<char, int> &windowFreq,
                     const unordered_map<char, int> &refFreq) {
        for (const auto &[ch, count] : refFreq) {
            if (windowFreq.at(ch) < count) {
                return false;
            }
        }
        return true;
    }
};

class Solution1Test : public ::testing::Test {
  protected:
    Solution1 solution;
};

TEST_F(Solution1Test, TestCase1) {
    string s = "ADOBECODEBANC";
    string t = "ABC";

    string actual = solution.minWindow(s, t);
    string expected = "BANC";

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase2) {
    string s = "a";
    string t = "a";

    string actual = solution.minWindow(s, t);
    string expected = "a";

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase3) {
    string s = "a";
    string t = "aa";

    string actual = solution.minWindow(s, t);
    string expected = "";

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase4) {
    string s = "ADOBECODEBANC";
    string t = "CDEEO";

    string actual = solution.minWindow(s, t);
    string expected = "ECODE";

    EXPECT_EQ(actual, expected);
}