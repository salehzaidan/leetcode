#include <gtest/gtest.h>
#include <string>
#include <vector>

using namespace std;

class Solution1 {
  public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> result;
        vector<string> partition;

        backtrack(s, result, partition, 0);

        return result;
    }

  private:
    void backtrack(const string &s, vector<vector<string>> &result,
                   vector<string> &partition, int index) {
        if (index == s.length()) {
            result.push_back(partition);
            return;
        }

        for (int i = index; i < s.length(); i++) {
            string substring(s.begin() + index, s.begin() + i + 1);
            if (!isPalindrome(substring)) {
                continue;
            }

            partition.push_back(substring);
            backtrack(s, result, partition, i + 1);
            partition.pop_back();
        }
    }

    bool isPalindrome(const string &s) {
        int left = 0;
        int right = s.length() - 1;
        while (left < right) {
            if (!isalnum(s[left])) {
                left++;
                continue;
            }

            if (!isalnum(s[right])) {
                right--;
                continue;
            }

            if (tolower(s[left]) != tolower(s[right])) {
                return false;
            }

            left++;
            right--;
        }

        return true;
    }
};

class Solution1Test : public ::testing::Test {
  protected:
    Solution1 solution;
};

TEST_F(Solution1Test, TestCase1) {
    string s = "aab";

    vector<vector<string>> actual = solution.partition(s);
    vector<vector<string>> expected = {{"a", "a", "b"}, {"aa", "b"}};

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase2) {
    string s = "a";

    vector<vector<string>> actual = solution.partition(s);
    vector<vector<string>> expected = {{"a"}};

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase3) {
    string s = "civic";

    vector<vector<string>> actual = solution.partition(s);
    vector<vector<string>> expected = {
        {"c", "i", "v", "i", "c"}, {"c", "ivi", "c"}, {"civic"}};

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase4) {
    string s = "racecar";

    vector<vector<string>> actual = solution.partition(s);
    vector<vector<string>> expected = {{"r", "a", "c", "e", "c", "a", "r"},
                                       {"r", "a", "cec", "a", "r"},
                                       {"r", "aceca", "r"},
                                       {"racecar"}};

    EXPECT_EQ(actual, expected);
}