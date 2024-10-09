#include <gtest/gtest.h>
#include <limits>
#include <stdexcept>

using namespace std;

class Solution1 {
public:
  double findMedianSortedArrays(const vector<int> &nums1,
                                const vector<int> &nums2) {
    const vector<int> &smaller = (nums1.size() <= nums2.size()) ? nums1 : nums2;
    const vector<int> &larger = (nums1.size() > nums2.size()) ? nums1 : nums2;

    const int m = smaller.size();
    const int n = larger.size();

    int left = 0;
    int right = m;
    while (left <= right) {
      int i = left + (right - left) / 2;
      int j = (m + n + 1) / 2 - i;

      int min1 = i == m ? numeric_limits<int>::max() : smaller[i];
      int max1 = i == 0 ? numeric_limits<int>::min() : smaller[i - 1];

      int min2 = j == n ? numeric_limits<int>::max() : larger[j];
      int max2 = j == 0 ? numeric_limits<int>::min() : larger[j - 1];

      if (max1 > min2) {
        right = i - 1;
      } else if (max2 > min1) {
        left = i + 1;
      } else {
        if (((m + n) & 1) == 0) {
          return (max(max1, max2) + min(min1, min2)) / (double)2;
        } else {
          return max(max1, max2);
        }
      }
    }

    throw runtime_error("Unreachable");
  }
};

class Solution1Test : public ::testing::Test {
protected:
  Solution1 solution;
};

TEST_F(Solution1Test, TestCase1) {
  vector<int> nums1 = {1, 3};
  vector<int> nums2 = {2};

  double actual = solution.findMedianSortedArrays(nums1, nums2);
  double expected = 2;

  EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase2) {
  vector<int> nums1 = {1, 2};
  vector<int> nums2 = {3, 4};

  double actual = solution.findMedianSortedArrays(nums1, nums2);
  double expected = 2.5;

  EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase3) {
  vector<int> nums1 = {7, 9, 10, 11};
  vector<int> nums2 = {1, 3, 8};

  double actual = solution.findMedianSortedArrays(nums1, nums2);
  double expected = 8;

  EXPECT_EQ(actual, expected);
}