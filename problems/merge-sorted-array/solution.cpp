#include <algorithm>
#include <gtest/gtest.h>
#include <iterator>
#include <limits>
#include <queue>
#include <vector>

using namespace std;

class Solution1 {
  public:
    void merge(vector<int> &nums1, int m, vector<int> &nums2, int n) {
        auto it2 = nums2.begin();
        priority_queue<int, vector<int>, greater<int>> buf;

        for (auto it1 = nums1.begin(); it1 != nums1.end(); it1++) {
            if (distance(nums1.begin(), it1) >= m) {
                *it1 = numeric_limits<int>::max();
            }

            if (it2 != nums2.end() && *it2 < *it1) {
                if (!buf.empty() && *it2 > buf.top()) {
                    retrieve(it1, buf);
                    continue;
                }
                consume(it1, it2, buf);
            } else if (!buf.empty() && buf.top() < *it1) {
                retrieve(it1, buf);
            }
        }
    }

    void consume(vector<int>::iterator &it1, vector<int>::iterator &it2,
                 priority_queue<int, vector<int>, greater<int>> &buf) {
        buf.push(*it1);
        *it1 = *it2;
        it2++;
    }

    void retrieve(vector<int>::iterator &it1,
                  priority_queue<int, vector<int>, greater<int>> &buf) {
        auto tmp = buf.top();
        buf.pop();
        swap(*it1, tmp);
        buf.push(tmp);
    }
};

TEST(Solution1, Merge1) {
    Solution1 solution;
    vector<int> nums1{1, 2, 3, 0, 0, 0};
    int m = 3;
    vector<int> nums2{2, 5, 6};
    int n = 3;
    vector<int> expected{1, 2, 2, 3, 5, 6};
    solution.merge(nums1, m, nums2, n);
    EXPECT_EQ(expected, nums1);
}

TEST(Solution1, Merge2) {
    Solution1 solution;
    vector<int> nums1{1};
    int m = 1;
    vector<int> nums2;
    int n = 0;
    vector<int> expected{1};
    solution.merge(nums1, m, nums2, n);
    EXPECT_EQ(expected, nums1);
}

TEST(Solution1, Merge3) {
    Solution1 solution;
    vector<int> nums1{0};
    int m = 0;
    vector<int> nums2{1};
    int n = 1;
    vector<int> expected{1};
    solution.merge(nums1, m, nums2, n);
    EXPECT_EQ(expected, nums1);
}

TEST(Solution1, Merge4) {
    Solution1 solution;
    vector<int> nums1{2, 0};
    int m = 1;
    vector<int> nums2{1};
    int n = 1;
    vector<int> expected{1, 2};
    solution.merge(nums1, m, nums2, n);
    EXPECT_EQ(expected, nums1);
}

TEST(Solution1, Merge5) {
    Solution1 solution;
    vector<int> nums1{4, 5, 6, 0, 0, 0};
    int m = 3;
    vector<int> nums2{1, 2, 3};
    int n = 3;
    vector<int> expected{1, 2, 3, 4, 5, 6};
    solution.merge(nums1, m, nums2, n);
    EXPECT_EQ(expected, nums1);
}

TEST(Solution1, Merge6) {
    Solution1 solution;
    vector<int> nums1{1, 2, 4, 5, 6, 0};
    int m = 5;
    vector<int> nums2{3};
    int n = 1;
    vector<int> expected{1, 2, 3, 4, 5, 6};
    solution.merge(nums1, m, nums2, n);
    EXPECT_EQ(expected, nums1);
}

TEST(Solution1, Merge7) {
    Solution1 solution;
    vector<int> nums1{-1, 0, 0, 3, 3, 3, 0, 0, 0};
    int m = 6;
    vector<int> nums2{1, 2, 2};
    int n = 3;
    vector<int> expected{-1, 0, 0, 1, 2, 2, 3, 3, 3};
    solution.merge(nums1, m, nums2, n);
    EXPECT_EQ(expected, nums1);
}

TEST(Solution1, Merge8) {
    Solution1 solution;
    vector<int> nums1{-1, 0, 1, 1, 0, 0, 0, 0, 0};
    int m = 4;
    vector<int> nums2{-1, 0, 2, 2, 3};
    int n = 5;
    vector<int> expected{-1, -1, 0, 0, 1, 1, 2, 2, 3};
    solution.merge(nums1, m, nums2, n);
    EXPECT_EQ(expected, nums1);
}

class Solution2 {
  public:
    void merge(vector<int> &nums1, int m, vector<int> &nums2, int n) {
        auto i = nums1.rbegin() + n;
        auto j = nums2.rbegin();
        auto k = nums1.rbegin();

        for (auto k = nums1.rbegin(); j != nums2.rend(); k++) {
            if (i != nums1.rend() && *i > *j) {
                *k = *i;
                i++;
            } else {
                *k = *j;
                j++;
            }
        }
    }
};

TEST(Solution2, Merge1) {
    Solution2 solution;
    vector<int> nums1{1, 2, 3, 0, 0, 0};
    int m = 3;
    vector<int> nums2{2, 5, 6};
    int n = 3;
    vector<int> expected{1, 2, 2, 3, 5, 6};
    solution.merge(nums1, m, nums2, n);
    EXPECT_EQ(expected, nums1);
}

TEST(Solution2, Merge2) {
    Solution2 solution;
    vector<int> nums1{1};
    int m = 1;
    vector<int> nums2;
    int n = 0;
    vector<int> expected{1};
    solution.merge(nums1, m, nums2, n);
    EXPECT_EQ(expected, nums1);
}

TEST(Solution2, Merge3) {
    Solution2 solution;
    vector<int> nums1{0};
    int m = 0;
    vector<int> nums2{1};
    int n = 1;
    vector<int> expected{1};
    solution.merge(nums1, m, nums2, n);
    EXPECT_EQ(expected, nums1);
}

TEST(Solution2, Merge4) {
    Solution2 solution;
    vector<int> nums1{2, 0};
    int m = 1;
    vector<int> nums2{1};
    int n = 1;
    vector<int> expected{1, 2};
    solution.merge(nums1, m, nums2, n);
    EXPECT_EQ(expected, nums1);
}

TEST(Solution2, Merge5) {
    Solution2 solution;
    vector<int> nums1{4, 5, 6, 0, 0, 0};
    int m = 3;
    vector<int> nums2{1, 2, 3};
    int n = 3;
    vector<int> expected{1, 2, 3, 4, 5, 6};
    solution.merge(nums1, m, nums2, n);
    EXPECT_EQ(expected, nums1);
}

TEST(Solution2, Merge6) {
    Solution2 solution;
    vector<int> nums1{1, 2, 4, 5, 6, 0};
    int m = 5;
    vector<int> nums2{3};
    int n = 1;
    vector<int> expected{1, 2, 3, 4, 5, 6};
    solution.merge(nums1, m, nums2, n);
    EXPECT_EQ(expected, nums1);
}

TEST(Solution2, Merge7) {
    Solution2 solution;
    vector<int> nums1{-1, 0, 0, 3, 3, 3, 0, 0, 0};
    int m = 6;
    vector<int> nums2{1, 2, 2};
    int n = 3;
    vector<int> expected{-1, 0, 0, 1, 2, 2, 3, 3, 3};
    solution.merge(nums1, m, nums2, n);
    EXPECT_EQ(expected, nums1);
}

TEST(Solution2, Merge8) {
    Solution2 solution;
    vector<int> nums1{-1, 0, 1, 1, 0, 0, 0, 0, 0};
    int m = 4;
    vector<int> nums2{-1, 0, 2, 2, 3};
    int n = 5;
    vector<int> expected{-1, -1, 0, 0, 1, 1, 2, 2, 3};
    solution.merge(nums1, m, nums2, n);
    EXPECT_EQ(expected, nums1);
}