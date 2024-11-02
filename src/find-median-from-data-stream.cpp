#include <gtest/gtest.h>
#include <queue>
#include <vector>

using namespace std;

class MedianFinder1 {
  public:
    MedianFinder1() { size = 0; }

    void addNum(int num) {
        if (maxHeap.empty() || num < maxHeap.top()) {
            maxHeap.push(num);
        } else {
            minHeap.push(num);
        }

        if ((int)(maxHeap.size() - minHeap.size()) > 1) {
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        } else if ((int)(minHeap.size() - maxHeap.size()) > 1) {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }

        size++;
    }

    double findMedian() {
        if (size % 2 == 0) {
            return (maxHeap.top() + minHeap.top()) / 2.0;
        } else if (maxHeap.size() > minHeap.size()) {
            return maxHeap.top();
        } else {
            return minHeap.top();
        }
    }

  private:
    int size;
    priority_queue<int, vector<int>, less<int>> maxHeap;
    priority_queue<int, vector<int>, greater<int>> minHeap;
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */

class MedianFinder1Test : public ::testing::Test {
  protected:
    double error = 1e-5;
    MedianFinder1 obj;
};

TEST_F(MedianFinder1Test, TestCase1) {
    obj.addNum(1);
    obj.addNum(2);
    EXPECT_NEAR(obj.findMedian(), 1.5, error);
    obj.addNum(3);
    EXPECT_NEAR(obj.findMedian(), 2.0, error);
}

TEST_F(MedianFinder1Test, TestCase2) {
    obj.addNum(5);
    obj.addNum(10);
    obj.addNum(15);
    EXPECT_NEAR(obj.findMedian(), 10.0, error);
    obj.addNum(20);
    EXPECT_NEAR(obj.findMedian(), 12.5, error);
}

TEST_F(MedianFinder1Test, TestCase3) {
    obj.addNum(1);
    obj.addNum(3);
    obj.addNum(2);
    EXPECT_NEAR(obj.findMedian(), 2.0, error);
    obj.addNum(4);
    EXPECT_NEAR(obj.findMedian(), 2.5, error);
}

TEST_F(MedianFinder1Test, TestCase4) {
    obj.addNum(7);
    obj.addNum(8);
    obj.addNum(9);
    obj.addNum(10);
    EXPECT_NEAR(obj.findMedian(), 8.5, error);
    obj.addNum(6);
    EXPECT_NEAR(obj.findMedian(), 8.0, error);
}

TEST_F(MedianFinder1Test, TestCase5) {
    obj.addNum(1);
    obj.addNum(100);
    obj.addNum(50);
    obj.addNum(25);
    EXPECT_NEAR(obj.findMedian(), 37.5, error);
    obj.addNum(75);
    EXPECT_NEAR(obj.findMedian(), 50.0, error);
}

TEST_F(MedianFinder1Test, TestCase6) {
    obj.addNum(-1);
    obj.addNum(-2);
    obj.addNum(-3);
    obj.addNum(-4);
    EXPECT_NEAR(obj.findMedian(), -2.5, error);
    obj.addNum(-5);
    EXPECT_NEAR(obj.findMedian(), -3.0, error);
}