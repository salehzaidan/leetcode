#include <gtest/gtest.h>
#include <queue>

using namespace std;

class Solution1 {
  public:
    int leastInterval(vector<char> &tasks, int n) {
        queue<pair<char, int>> cooldown;
        const int alphabetSize = 26;
        array<int, alphabetSize> freq;

        for (char task : tasks) {
            freq[task - 'A']++;
        }

        auto comp = [&](const char &a, const char &b) {
            return freq[a - 'A'] < freq[b - 'A'];
        };
        priority_queue<char, vector<char>, decltype(comp)> heap(comp);

        for (int i = 0; i < freq.size(); i++) {
            if (freq[i] != 0) {
                heap.push(i + 'A');
            }
        }

        int interval = 0;
        for (; !cooldown.empty() || !heap.empty(); interval++) {
            if (interval < cooldown.size()) {
                auto [task, available] = cooldown.front();
                if (available <= interval) {
                    cooldown.pop();
                    heap.push(task);
                }
            }

            if (!heap.empty()) {
                char task = heap.top();
                heap.pop();
                int &f = freq[task - 'A'];
                f--;

                if (f > 0) {
                    cooldown.push({task, interval + n + 1});
                }
            }
        }

        return interval;
    }
};

class Solution1Test : public ::testing::Test {
  protected:
    Solution1 solution;
};

TEST_F(Solution1Test, TestCase1) {
    vector<char> tasks = {'A', 'A', 'A', 'B', 'B', 'B'};
    int n = 2;

    int actual = solution.leastInterval(tasks, n);
    int expected = 8;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase2) {
    vector<char> tasks = {'A', 'C', 'A', 'B', 'D', 'B'};
    int n = 1;

    int actual = solution.leastInterval(tasks, n);
    int expected = 6;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase3) {
    vector<char> tasks = {'A', 'A', 'A', 'B', 'B', 'B'};
    int n = 3;

    int actual = solution.leastInterval(tasks, n);
    int expected = 10;

    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase4) {
    vector<char> tasks = {'A', 'B', 'A'};
    int n = 2;

    int actual = solution.leastInterval(tasks, n);
    int expected = 4;

    EXPECT_EQ(actual, expected);
}