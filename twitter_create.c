//
// Created by chaai on 7/4/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "twitter_create.h"


void printUsers(userPtr userList)       //print all users in the linked list
{
    if(userList == NULL)        //the list is empty.
    {
        puts("No user available");
    }
    else
    {
        while(userList != NULL)     //loop through every user in the list
        {
            printf("User: %s; Followers: %d; Following: %d\n",userList -> username, userList -> num_followers, userList -> num_followers );
            userList = userList -> nextPtr;
        }
    }
}

void printTweets(tweetPtr tweetList, char viewingUser[USR_LENGTH])
{
    //to be done.
}

void insertUser(userPtr* userList, char username[USR_LENGTH])
{
    userPtr previousNode = NULL;
    userPtr currentNode = *userList;
    userPtr newNode = (userPtr)malloc(sizeof(user));
    strcpy(newNode -> username, username);
    newNode -> num_followers = 0;
    newNode -> num_following = 0;
    newNode -> nextPtr = NULL;

    while(currentNode != NULL)      //loop to the last place in the list.
    {
        previousNode = currentNode;
        currentNode = currentNode -> nextPtr;
    }

    if(previousNode == NULL)        //first one in the list.
    {
        *userList = newNode;
    }
    else
    {
        previousNode -> nextPtr = newNode;      //points the previous node's pointer to the new node.
    }
}
void insertTweet(tweetPtr* tweetList, char msg[TWEET_LENGTH], int* id, char author[USR_LENGTH])
{
    tweetPtr previousNode = NULL;
    tweetPtr currentNode = *tweetList;
    tweetPtr newTweetNode = (tweetPtr)malloc(sizeof(tweet));
    strcpy(newTweetNode -> msg, msg);
    newTweetNode -> id = *id;
    *id = *id +1;       //change the total number of tweets.
    strcpy(newTweetNode -> user, author);
    newTweetNode -> nextPtr = NULL;

    while(currentNode != NULL)
    {
        previousNode = currentNode;
        currentNode = currentNode -> nextPtr;
    }

    if(previousNode == NULL)
    {
        *tweetList = newTweetNode;
    }
    else
    {
        previousNode -> nextPtr = newTweetNode;
    }


}

void printKeyInfo();

void create_twitter_system(twitter * twitter_system){
    
    printKeyInfo();
    twitter_system->num_users = 0;
    twitter_system ->num_tweets = 0;
    size_t choice;
    scanf("%u",&choice);
    fflush(stdin);

    while (choice >=0 && choice <= 6){
        switch (choice) {
            case 0:
                createUsers( twitter_system);
                break;
            case 1:
                postTweets(twitter_system);
                break;
            case 2:
                followUsers(twitter_system);
                break;
            case 3:
                unfollowUsers(twitter_system);
                break;
            case 4:
                deleteUser(twitter_system);
                break;
            case 5:
                endTurn(twitter_system);
                break;
            case 6:
                endTwitter(twitter_system);
                break;
        }

        printKeyInfo();
        scanf("%u",&choice);
        fflush(stdin);
    }
}

void createUsers(twitter* twitter_system){      //create user and prints all available users.
    char username[USR_LENGTH];
    printf("Enter Username: ");
    fgets(username, USR_LENGTH, stdin);     //use fgets to scan string

    if(username[strlen(username)-1] =='\n')     //replace the newline char with null char.
        username[strlen(username)-1] = '\0';

    strcpy(twitter_system->users[twitter_system->num_users].username, username);
    twitter_system-> users[twitter_system->num_users].num_followers = 0;
    twitter_system->users[twitter_system->num_users].num_following = 0;
    twitter_system->num_users += 1;     //total number of user increase by 1.

    //This is a print to show all the information when creating the users
    for(int i =0; i < twitter_system->num_users; i++){
        user usr = twitter_system->users[i];
        printf("User: %s; Followers: %d; Following: %d\n",usr.username, usr.num_followers, usr.num_followers );
    }
    puts("");
}

void postTweets(twitter* twitter_system){
    printf("Test for postTweets success.\n");
    char tweetInput[270];
    puts("Enter your tweet: ");

}

void followUsers(twitter* twitter_system){
    printf("Test for followUSers success.\n");
}

void unfollowUsers(twitter* twitter_system){
    printf("Test for unfollowUsers success.\n");
}

void deleteUser(twitter* twitter_system){
    printf("Test for deleteUSer success.\n");
}

void endTurn(twitter* twitter_system){
    printf("Test for endTurn success.\n");
}

void endTwitter(twitter* twitter_system){
    printf("Test for endTwitter success.\n");
}

void printKeyInfo(){
    printf("Enter the number between 0 and 6:\n");
    printf("Enter 0: Create a user\n");
    printf("Enter 1: Post tweets\n");
    printf("Enter 2: Follow users\n");
    printf("Enter 3: Unfollow users\n");
    printf("Enter 4: delete the user\n");
    printf("Enter 5: End this turn\n");
    printf("Enter 6: End the Twitter system\n");
}