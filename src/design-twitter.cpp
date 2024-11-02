#include <algorithm>
#include <forward_list>
#include <gtest/gtest.h>
#include <queue>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Twitter1 {
  public:
    Twitter1() { time = 0; }

    void postTweet(int userId, int tweetId) {
        pool.push_front({.id = tweetId, .userId = userId, .time = time++});
        Tweet *tweet = &pool.front();

        insertTweet(feeds[userId], tweet);

        for (auto [followerId, followees] : following) {
            if (followees.contains(userId)) {
                insertTweet(feeds[followerId], tweet);
            }
        }
    }

    vector<int> getNewsFeed(int userId) {
        vector<int> result;
        auto feed = feeds[userId];

        while (!feed.empty()) {
            result.push_back(feed.top()->id);
            feed.pop();
        }

        reverse(result.begin(), result.end());
        return result;
    }

    void follow(int followerId, int followeeId) {
        if (following[followerId].contains(followeeId)) {
            return;
        }

        following[followerId].insert(followeeId);

        for (Tweet &tweet : pool) {
            if (tweet.userId == followeeId) {
                insertTweet(feeds[followerId], &tweet);
            }
        }
    }

    void unfollow(int followerId, int followeeId) {
        if (!following[followerId].contains(followeeId)) {
            return;
        }

        following[followerId].erase(followeeId);
        priority_queue<Tweet *, vector<Tweet *>, TweetCompare> feed;

        for (Tweet &tweet : pool) {
            if (tweet.userId == followerId ||
                following[followerId].contains(tweet.userId)) {
                insertTweet(feed, &tweet);
            }
        }

        feeds[followerId] = std::move(feed);
    }

  private:
    struct Tweet {
        int id;
        int userId;
        int time;
    };

    struct TweetCompare {
        bool operator()(const Tweet *a, const Tweet *b) {
            return a->time > b->time;
        }
    };

    int time;
    forward_list<Tweet> pool;
    unordered_map<int, unordered_set<int>> following;
    unordered_map<int, priority_queue<Tweet *, vector<Tweet *>, TweetCompare>>
        feeds;

    static const int MAX_TWEETS = 10;

    static void
    insertTweet(priority_queue<Tweet *, vector<Tweet *>, TweetCompare> &q,
                Tweet *tweet) {
        q.push(tweet);
        if (q.size() > MAX_TWEETS) {
            q.pop();
        }
    }
};

/**
 * Your Twitter object will be instantiated and called as such:
 * Twitter* obj = new Twitter();
 * obj->postTweet(userId,tweetId);
 * vector<int> param_2 = obj->getNewsFeed(userId);
 * obj->follow(followerId,followeeId);
 * obj->unfollow(followerId,followeeId);
 */

class Twitter1Test : public ::testing::Test {
  protected:
    Twitter1 obj;
};

TEST_F(Twitter1Test, TestCase1) {
    vector<int> expected;
    obj.postTweet(1, 5);
    expected = {5};
    EXPECT_EQ(obj.getNewsFeed(1), expected);
}

TEST_F(Twitter1Test, TestCase2) {
    vector<int> expected;
    obj.postTweet(1, 10);
    obj.postTweet(1, 15);
    expected = {15, 10};
    EXPECT_EQ(obj.getNewsFeed(1), expected);
}

TEST_F(Twitter1Test, TestCase3) {
    vector<int> expected;
    obj.postTweet(1, 15);
    obj.follow(1, 2);
    obj.postTweet(2, 20);
    expected = {20, 15};
    EXPECT_EQ(obj.getNewsFeed(1), expected);
}

TEST_F(Twitter1Test, TestCase4) {
    vector<int> expected;
    obj.postTweet(1, 15);
    obj.postTweet(2, 25);
    obj.follow(1, 2);
    obj.postTweet(3, 30);
    obj.follow(1, 3);
    expected = {30, 25, 15};
    EXPECT_EQ(obj.getNewsFeed(1), expected);
}

TEST_F(Twitter1Test, TestCase5) {
    vector<int> expected;
    obj.postTweet(1, 15);
    obj.postTweet(2, 25);
    obj.follow(1, 2);
    obj.unfollow(1, 2);
    expected = {15};
    EXPECT_EQ(obj.getNewsFeed(1), expected);
}

TEST_F(Twitter1Test, TestCase6) {
    vector<int> expected;
    expected = {};
    EXPECT_EQ(obj.getNewsFeed(1), expected);
}

TEST_F(Twitter1Test, TestCase7) {
    const int numTweets = 100;
    vector<int> expected;
    for (int i = 1; i <= numTweets; i++) {
        if (i <= 10) {
            expected.push_back(numTweets - i + 1);
        }
        obj.postTweet(1, i);
    }
    EXPECT_EQ(obj.getNewsFeed(1), expected);
}

TEST_F(Twitter1Test, TestCase8) {
    vector<int> expected;
    obj.postTweet(2, 5);
    obj.follow(1, 2);
    obj.follow(1, 2);
    expected = {5};
    EXPECT_EQ(obj.getNewsFeed(1), expected);
}

TEST_F(Twitter1Test, TestCase9) {
    vector<int> expected;
    obj.postTweet(1, 5);
    obj.postTweet(2, 3);
    obj.postTweet(1, 101);
    obj.postTweet(2, 13);
    obj.postTweet(2, 10);
    obj.postTweet(1, 2);
    obj.postTweet(1, 94);
    obj.postTweet(2, 505);
    obj.postTweet(1, 333);
    obj.postTweet(2, 22);
    obj.postTweet(1, 11);
    obj.postTweet(1, 205);
    obj.postTweet(2, 203);
    obj.postTweet(1, 201);
    obj.postTweet(2, 213);
    obj.postTweet(1, 200);
    obj.postTweet(2, 202);
    obj.postTweet(1, 204);
    obj.postTweet(2, 208);
    obj.postTweet(2, 233);
    obj.postTweet(1, 222);
    obj.postTweet(2, 211);
    expected = {222, 204, 200, 201, 205, 11, 333, 94, 2, 101};
    EXPECT_EQ(obj.getNewsFeed(1), expected);
    obj.follow(1, 2);
    obj.getNewsFeed(1);
    expected = {211, 222, 233, 208, 204, 202, 200, 213, 201, 203};
    EXPECT_EQ(obj.getNewsFeed(1), expected);
    obj.unfollow(1, 2);
    expected = {222, 204, 200, 201, 205, 11, 333, 94, 2, 101};
    EXPECT_EQ(obj.getNewsFeed(1), expected);
}