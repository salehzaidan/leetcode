#include <gtest/gtest.h>
#include <vector>

using namespace std;

class Solution1 {
  public:
    int trap(vector<int> &height) {
        if (height.size() < 3) {
            return 0;
        }

        vector<int> maxLeftHeight(height.size(), height.front());
        for (int i = 1; i < height.size(); i++) {
            maxLeftHeight[i] = max(maxLeftHeight[i - 1], height[i]);
        }

        vector<int> maxRightHeight(height.size(), height.back());
        for (int i = height.size() - 2; i >= 0; i--) {
            maxRightHeight[i] = max(maxRightHeight[i + 1], height[i]);
        }

        int result = 0;

        for (int i = 1; i < height.size() - 1; i++) {
            int wall = min(maxLeftHeight[i - 1], maxRightHeight[i + 1]);
            result += max(0, wall - height[i]);
        }

        return result;
    }
};

TEST(Solution1, testCase1) {
    vector<int> height = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};

    Solution1 solution;
    EXPECT_EQ(solution.trap(height), 6);
}

TEST(Solution1, testCase2) {
    vector<int> height = {4, 2, 0, 3, 2, 5};

    Solution1 solution;
    EXPECT_EQ(solution.trap(height), 9);
}

TEST(Solution1, testCase3) {
    vector<int> height = {4, 2, 3};

    Solution1 solution;
    EXPECT_EQ(solution.trap(height), 1);
}

class Solution2 {
  public:
    int trap(vector<int> &height) {
        int result = 0;

        int maxLeft = height.front();
        int maxRight = height.back();

        int left = 0;
        int right = height.size() - 1;
        while (left < right) {
            if (maxLeft <= maxRight) {
                left++;
                result += max(0, maxLeft - height[left]);
                maxLeft = max(maxLeft, height[left]);
            } else {
                right--;
                result += max(0, maxRight - height[right]);
                maxRight = max(maxRight, height[right]);
            }
        }

        return result;
    }
};

TEST(Solution2, testCase1) {
    vector<int> height = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};

    Solution2 solution;
    EXPECT_EQ(solution.trap(height), 6);
}

TEST(Solution2, testCase2) {
    vector<int> height = {4, 2, 0, 3, 2, 5};

    Solution2 solution;
    EXPECT_EQ(solution.trap(height), 9);
}

TEST(Solution2, testCase3) {
    vector<int> height = {4, 2, 3};

    Solution2 solution;
    EXPECT_EQ(solution.trap(height), 1);
}