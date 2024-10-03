#include <algorithm>
#include <gtest/gtest.h>
#include <string>
#include <unordered_map>

using namespace std;

void sortGroups(vector<vector<string>> &groups) {
  for (vector<string> &group : groups) {
    sort(group.begin(), group.end());
  }
  sort(groups.begin(), groups.end());
}

class Solution1 {
public:
  vector<vector<string>> groupAnagrams(const vector<string> &strs) {
    unordered_map<string, vector<string>> anagrams;

    for (const string &str : strs) {
      string copy = str;
      sort(copy.begin(), copy.end());
      anagrams[copy].push_back(str);
    }

    vector<vector<string>> groups;
    for (const auto &entry : anagrams) {
      vector<string> group = entry.second;
      groups.push_back(group);
    }
    return groups;
  }
};

TEST(Solution1, testCase1) {
  vector<string> strs = {"eat", "tea", "tan", "ate", "nat", "bat"};

  vector<vector<string>> expected = {
      {"bat"}, {"nat", "tan"}, {"ate", "eat", "tea"}};
  sortGroups(expected);

  Solution1 solution;
  vector<vector<string>> groups = solution.groupAnagrams(strs);
  sortGroups(groups);
  EXPECT_EQ(groups, expected);
}

TEST(Solution1, testCase2) {
  vector<string> strs = {""};

  vector<vector<string>> expected = {{""}};
  sortGroups(expected);

  Solution1 solution;
  vector<vector<string>> groups = solution.groupAnagrams(strs);
  sortGroups(groups);
  EXPECT_EQ(groups, expected);
}