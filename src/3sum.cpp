#include <algorithm>
#include <gtest/gtest.h>
#include <vector>

using namespace std;

void sortTriplets(vector<vector<int>> &triplets) {
    for (vector<int> &triplet : triplets) {
        sort(triplet.begin(), triplet.end());
    }
    sort(triplets.begin(), triplets.end());
}

class Solution1 {
  public:
    vector<vector<int>> threeSum(const vector<int> &nums) {
        vector<int> copy = nums;
        sort(copy.begin(), copy.end());

        vector<vector<int>> triplets;

        for (int i = 0; i < copy.size(); i++) {
            if (i > 0 && copy[i] == copy[i - 1]) {
                continue;
            }

            int target = -copy[i];
            int j = i + 1;
            int k = copy.size() - 1;
            while (j < k) {
                int sum = copy[j] + copy[k];
                if (sum == target) {
                    vector<int> triplet = {copy[i], copy[j], copy[k]};
                    triplets.push_back(triplet);
                    while (j < k && copy[j] == triplet[1]) {
                        j++;
                    }
                    while (j < k && copy[k] == triplet[2]) {
                        k--;
                    }
                } else if (sum < target) {
                    j++;
                } else {
                    k--;
                }
            }
        }

        return triplets;
    }
};

TEST(Solution1, testCase1) {
    vector<int> nums = {-1, 0, 1, 2, -1, -4};

    vector<vector<int>> expected = {{-1, -1, 2}, {-1, 0, 1}};
    sortTriplets(expected);

    Solution1 solution;
    vector<vector<int>> triplets = solution.threeSum(nums);
    sortTriplets(triplets);
    EXPECT_EQ(triplets, expected);
}

TEST(Solution1, testCase2) {
    vector<int> nums = {0, 1, 1};

    vector<vector<int>> expected = {};
    sortTriplets(expected);

    Solution1 solution;
    vector<vector<int>> triplets = solution.threeSum(nums);
    sortTriplets(triplets);
    EXPECT_EQ(triplets, expected);
}

TEST(Solution1, testCase3) {
    vector<int> nums = {0, 0, 0};

    vector<vector<int>> expected = {{0, 0, 0}};
    sortTriplets(expected);

    Solution1 solution;
    vector<vector<int>> triplets = solution.threeSum(nums);
    sortTriplets(triplets);
    EXPECT_EQ(triplets, expected);
}

TEST(Solution1, testCase4) {
    vector<int> nums = {1, 2, -3, 1, 2, -3};

    vector<vector<int>> expected = {{-3, 1, 2}};
    sortTriplets(expected);

    Solution1 solution;
    vector<vector<int>> triplets = solution.threeSum(nums);
    sortTriplets(triplets);
    EXPECT_EQ(triplets, expected);
}

TEST(Solution1, testCase5) {
    vector<int> nums = {-1, 0, 1, 2, -1, -4, -2, -3, 3, 0, 4};

    vector<vector<int>> expected = {{-4, 0, 4}, {-4, 1, 3},  {-3, -1, 4},
                                    {-3, 0, 3}, {-3, 1, 2},  {-2, -1, 3},
                                    {-2, 0, 2}, {-1, -1, 2}, {-1, 0, 1}};
    sortTriplets(expected);

    Solution1 solution;
    vector<vector<int>> triplets = solution.threeSum(nums);
    sortTriplets(triplets);
    EXPECT_EQ(triplets, expected);
}