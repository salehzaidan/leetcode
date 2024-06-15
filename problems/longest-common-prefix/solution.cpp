#include <algorithm>
#include <gtest/gtest.h>
#include <string>
#include <vector>

using namespace std;

class Solution {
  public:
    string longestCommonPrefix(vector<string> &strs) {
        auto lcp = strs.front();

        for (size_t i = 1; i < strs.size(); i++) {
            auto s = strs.at(i);
            auto minsize = min(lcp.size(), s.size());
            auto mismatch = false;

            for (size_t j = 0; j < minsize; j++) {
                if (lcp.at(j) != s.at(j)) {
                    lcp.erase(j);
                    mismatch = true;
                    break;
                }
            }

            if (lcp.empty()) {
                break;
            }

            if (!mismatch && s.size() < lcp.size()) {
                lcp = s;
            }
        }

        return lcp;
    }
};

TEST(Solution, LongestCommonPrefix1) {
    Solution solution;
    string expected("fl");
    vector<string> strs{"flower", "flow", "flight"};
    string actual = solution.longestCommonPrefix(strs);
    EXPECT_EQ(expected, actual);
}

TEST(Solution, LongestCommonPrefix2) {
    Solution solution;
    string expected("");
    vector<string> strs{"dog", "racecar", "car"};
    string actual = solution.longestCommonPrefix(strs);
    EXPECT_EQ(expected, actual);
}

TEST(Solution, LongestCommonPrefix3) {
    Solution solution;
    string expected("aa");
    vector<string> strs{"aaa", "aa", "aaa"};
    string actual = solution.longestCommonPrefix(strs);
    EXPECT_EQ(expected, actual);
}
