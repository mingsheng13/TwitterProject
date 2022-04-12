//
// Created by chaai on 7/4/2022.
//

#ifndef NEWPROJECT_TWITTER_CREATE_H
#define NEWPROJECT_TWITTER_CREATE_H

#endif //NEWPROJECT_TWITTER_CREATE_H

#define TWEET_LENGTH 270
#define USR_LENGTH 100
#define MAX_FOLLOWERS 30
#define MAX_FOLLOWING 30
#define MAX_TWEETS 100
#define MAX_USERS 100

typedef struct tweet{
    int id;
    char msg[TWEET_LENGTH];
    char user[USR_LENGTH];
    struct tweet* nextPtr;

}tweet;

typedef struct tweet * tweetPtr;

typedef struct user{
    char username[USR_LENGTH];
    char followers[MAX_FOLLOWERS];
    int num_followers;
    char following[MAX_FOLLOWING];
    int num_following;
    struct user* nextPtr;

}user;

typedef user* userPtr;

typedef struct twitter{
    tweetPtr news_feed;
    userPtr username;
    int num_tweets;
    int num_users;

} twitter;

void create_twitter_system(twitter * twitter_system);
void createUsers(twitter * twitter_system);
void postTweets(twitter * twitter_system);
void followUsers(twitter * twitter_system);
void unfollowUsers(twitter * twitter_system);
void deleteUser(userPtr* userList);
void endTurn(twitter * twitter_system);
void endTwitter();
