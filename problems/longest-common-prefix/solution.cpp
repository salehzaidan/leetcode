#include <algorithm>
#include <gtest/gtest.h>
#include <iterator>
#include <string>
#include <vector>

using namespace std;

class Solution1 {
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

TEST(Solution1, LongestCommonPrefix1) {
    Solution1 solution;
    string expected("fl");
    vector<string> strs{"flower", "flow", "flight"};
    string actual = solution.longestCommonPrefix(strs);
    EXPECT_EQ(expected, actual);
}

TEST(Solution1, LongestCommonPrefix2) {
    Solution1 solution;
    string expected("");
    vector<string> strs{"dog", "racecar", "car"};
    string actual = solution.longestCommonPrefix(strs);
    EXPECT_EQ(expected, actual);
}

TEST(Solution1, LongestCommonPrefix3) {
    Solution1 solution;
    string expected("aa");
    vector<string> strs{"aaa", "aa", "aaa"};
    string actual = solution.longestCommonPrefix(strs);
    EXPECT_EQ(expected, actual);
}

class Solution2 {
  public:
    string longestCommonPrefix(vector<string> &strs) {
        string lcp;
        auto minit = min_element(strs.begin(), strs.end(),
                                 [](const string &a, const string &b) {
                                     return a.size() < b.size();
                                 });
        for (size_t i = 0; i < minit->size(); i++) {
            auto mismatch = false;
            for (size_t j = 0; j < strs.size() - 1; j++) {
                auto now = strs.at(j);
                auto next = strs.at(j + 1);
                if (now.at(i) != next.at(i)) {
                    mismatch = true;
                    break;
                }
            }

            if (mismatch) {
                break;
            }

            lcp = strs.front().substr(0, i + 1);
        }

        return lcp;
    }
};

TEST(Solution2, LongestCommonPrefix1) {
    Solution2 solution;
    string expected("fl");
    vector<string> strs{"flower", "flow", "flight"};
    string actual = solution.longestCommonPrefix(strs);
    EXPECT_EQ(expected, actual);
}

TEST(Solution2, LongestCommonPrefix2) {
    Solution2 solution;
    string expected("");
    vector<string> strs{"dog", "racecar", "car"};
    string actual = solution.longestCommonPrefix(strs);
    EXPECT_EQ(expected, actual);
}

TEST(Solution2, LongestCommonPrefix3) {
    Solution2 solution;
    string expected("aa");
    vector<string> strs{"aaa", "aa", "aaa"};
    string actual = solution.longestCommonPrefix(strs);
    EXPECT_EQ(expected, actual);
}

TEST(Solution2, LongestCommonPrefix4) {
    Solution2 solution;
    string expected("");
    vector<string> strs{"", ""};
    string actual = solution.longestCommonPrefix(strs);
    EXPECT_EQ(expected, actual);
}
