#include <gtest/gtest.h>
#include <queue>

using namespace std;

class KthLargest1 {
  public:
    KthLargest1(int k, vector<int> &nums) {
        this->k = k;
        for (int num : nums) {
            insert(num);
        }
    }

    int add(int val) {
        insert(val);
        return q.top();
    }

  private:
    int k;
    priority_queue<int, vector<int>, greater<int>> q;

    void insert(int val) {
        q.push(val);
        if (q.size() > k) {
            q.pop();
        }
    }
};

TEST(KthLargest1Test, TestCase1) {
    int k = 3;
    vector<int> nums = {4, 5, 8, 2};
    KthLargest1 kthLargest(k, nums);
    EXPECT_EQ(kthLargest.add(3), 4);
    EXPECT_EQ(kthLargest.add(5), 5);
    EXPECT_EQ(kthLargest.add(10), 5);
    EXPECT_EQ(kthLargest.add(9), 8);
    EXPECT_EQ(kthLargest.add(4), 8);
}

TEST(KthLargest1Test, TestCase2) {
    int k = 4;
    vector<int> nums = {7, 7, 7, 7, 8, 3};
    KthLargest1 kthLargest(k, nums);
    EXPECT_EQ(kthLargest.add(2), 7);
    EXPECT_EQ(kthLargest.add(10), 7);
    EXPECT_EQ(kthLargest.add(9), 7);
    EXPECT_EQ(kthLargest.add(9), 8);
}

class KthLargest2 {
  public:
    KthLargest2(int k, vector<int> &nums) {
        this->k = k;
        for (int num : nums) {
            insert(num);
        }
    }

    int add(int val) {
        insert(val);
        return arr.front();
    }

  private:
    int k;
    vector<int> arr;

    void insert(int val) {
        arr.push_back(val);
        int i = arr.size() - 1;

        while (i > 0) {
            int parent = (i - 1) / 2;
            if (arr[i] >= arr[parent]) {
                break;
            }

            swap(arr[i], arr[parent]);
            i = parent;
        }

        if (arr.size() > k) {
            arr.front() = arr.back();
            arr.pop_back();
            minHeapify(0);
        }
    }

    void minHeapify(int i) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;
        if (left < arr.size() && arr[left] < arr[smallest]) {
            smallest = left;
        }
        if (right < arr.size() && arr[right] < arr[smallest]) {
            smallest = right;
        }
        if (smallest != i) {
            swap(arr[i], arr[smallest]);
            minHeapify(smallest);
        }
    }
};

TEST(KthLargest2Test, TestCase1) {
    int k = 3;
    vector<int> nums = {4, 5, 8, 2};
    KthLargest2 kthLargest(k, nums);
    EXPECT_EQ(kthLargest.add(3), 4);
    EXPECT_EQ(kthLargest.add(5), 5);
    EXPECT_EQ(kthLargest.add(10), 5);
    EXPECT_EQ(kthLargest.add(9), 8);
    EXPECT_EQ(kthLargest.add(4), 8);
}

TEST(KthLargest2Test, TestCase2) {
    int k = 4;
    vector<int> nums = {7, 7, 7, 7, 8, 3};
    KthLargest2 kthLargest(k, nums);
    EXPECT_EQ(kthLargest.add(2), 7);
    EXPECT_EQ(kthLargest.add(10), 7);
    EXPECT_EQ(kthLargest.add(9), 7);
    EXPECT_EQ(kthLargest.add(9), 8);
}