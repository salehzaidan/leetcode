#include <array>
#include <gtest/gtest.h>
#include <string>
#include <vector>

using namespace std;

class Solution1 {
  public:
    vector<string> letterCombinations(string digits) {
        vector<string> result;

        if (digits.empty()) {
            return result;
        }

        array<string, 10> phoneLetters;
        phoneLetters[2] = "abc";
        phoneLetters[3] = "def";
        phoneLetters[4] = "ghi";
        phoneLetters[5] = "jkl";
        phoneLetters[6] = "mno";
        phoneLetters[7] = "pqrs";
        phoneLetters[8] = "tuv";
        phoneLetters[9] = "wxyz";

        string combination;

        backtrack(digits, result, phoneLetters, combination, 0);

        return result;
    }

  private:
    void backtrack(const string &digits, vector<string> &result,
                   const array<string, 10> &phoneLetters, string &combination,
                   int index) {
        if (index == digits.length()) {
            result.push_back(combination);
            return;
        }

        int digit = digits[index] - '0';
        const string &letters = phoneLetters[digit];

        for (char letter : letters) {
            combination.push_back(letter);
            backtrack(digits, result, phoneLetters, combination, index + 1);
            combination.pop_back();
        }
    }
};

class Solution1Test : public ::testing::Test {
  protected:
    Solution1 solution;
};

TEST_F(Solution1Test, TestCase1) {
    string digits = "23";

    vector<string> actual = solution.letterCombinations(digits);
    vector<string> expected = {"ad", "ae", "af", "bd", "be",
                               "bf", "cd", "ce", "cf"};

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase2) {
    string digits = "";

    vector<string> actual = solution.letterCombinations(digits);
    vector<string> expected = {};

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase3) {
    string digits = "2";

    vector<string> actual = solution.letterCombinations(digits);
    vector<string> expected = {"a", "b", "c"};

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase4) {
    string digits = "234";

    vector<string> actual = solution.letterCombinations(digits);
    vector<string> expected = {"adg", "adh", "adi", "aeg", "aeh", "aei", "afg",
                               "afh", "afi", "bdg", "bdh", "bdi", "beg", "beh",
                               "bei", "bfg", "bfh", "bfi", "cdg", "cdh", "cdi",
                               "ceg", "ceh", "cei", "cfg", "cfh", "cfi"};

    EXPECT_EQ(actual, expected);
}