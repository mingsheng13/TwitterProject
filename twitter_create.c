//
// Created by chaai on 7/4/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "twitter_create.h"


void printUsers(userPtr userList);       //print all users in the linked list
void printTweets(tweetPtr tweetList, char viewingUser[USR_LENGTH]);
void insertUser(userPtr* userList, char username[USR_LENGTH]);
void insertTweet(tweetPtr* tweetList, char msg[TWEET_LENGTH], int* id, char author[USR_LENGTH]);

void printKeyInfo();

void create_twitter_system(twitter * twitter_system){
    
    printKeyInfo();
    twitter_system -> num_users = 0;
    twitter_system -> num_tweets = 0;
    twitter_system -> username = NULL;      //init. the username linked list
    twitter_system -> news_feed = NULL;
    unsigned int choice;
    scanf("%u", &choice);
    fflush(stdin);

    while (choice >= 0 && choice <= 6){
        switch (choice) {
            case 0:
                createUsers(twitter_system);
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
                deleteUser(&twitter_system -> username);
                break;
            case 5:
                endTurn(twitter_system);
                break;
            case 6:
                endTwitter();
                break;
            default:
                puts("error");
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

    insertUser(&twitter_system -> username, username);      //insert username into linkedList

    twitter_system -> num_users += 1;

    printUsers(twitter_system -> username);

    puts("");
}

void postTweets(twitter* twitter_system){
    //printf("Test for postTweets success.\n");
    //tweetPtr currentNode = *tweet;
    char tweetInput[TWEET_LENGTH];
    puts("Enter your tweet: ");
    fgets(tweetInput,TWEET_LENGTH,stdin);

    insertTweet(&twitter_system -> news_feed,tweetInput,&twitter_system -> num_tweets ,twitter_system -> username);

    twitter_system -> num_tweets += 1;

    printTweets(twitter_system -> news_feed,twitter_system -> username);
}

void followUsers(twitter* twitter_system){
    printf("Test for followUsers success.\n");
}

void unfollowUsers(twitter* twitter_system){
    printf("Test for unfollowUsers success.\n");
}

void deleteUser(userPtr* userList){
    //link the previous node to next node and use free()
    char username[USR_LENGTH];
    userPtr previousPtr = NULL;
    userPtr currentPtr = *userList;

    if(currentPtr == NULL)
    {
        puts("User list is empty!");
        return;
    }

    printUsers(*userList);
    printf("Enter the username that you want to delete:");
    fgets(username, USR_LENGTH, stdin);     //use fgets to scan string

    if(username[strlen(username)-1] =='\n')     //replace the newline char with null char.
        username[strlen(username)-1] = '\0';

    while(currentPtr != NULL && strcmp(currentPtr -> username, username) != 0)      //loop through the list and
    {                                                                               //stop if the username is found
        previousPtr = currentPtr;
        currentPtr = currentPtr -> nextPtr;
    }
    if(previousPtr == NULL)
    {
        *userList = currentPtr -> nextPtr;
    }
    else if(strcmp(currentPtr -> username, username) == 0)
    {
        previousPtr -> nextPtr = currentPtr -> nextPtr;
        free(currentPtr);
    }
    else
    {
        puts("Error username entered! ");
        return;
    }

}

void endTurn(twitter* twitter_system){
    printf("Test for endTurn success.\n");
}

void endTwitter(){
    printf("Thank you for using.\n");
    exit(0);
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
            printf("User: %s; Followers: %d; Following: %d\n" ,userList -> username, userList -> num_followers, userList -> num_followers );
            userList = userList -> nextPtr;
        }
    }
}

void insertUser(userPtr* userList, char username[USR_LENGTH])
{
    userPtr previousNode = NULL;
    userPtr currentNode = *userList;
    userPtr newNode = (userPtr)malloc(sizeof(user));        //allocate memory
    if(newNode == NULL)
    {
        printf("error allocating memory");
        exit(0);
    }
    strcpy(newNode -> username, username);
    newNode -> num_followers = 0;
    newNode -> num_following = 0;
    newNode -> nextPtr = NULL;      //since we are only appending, the newNode's nextPtr always points to NULL

    while(currentNode != NULL)      //loop to the last place in the list.
    {
        if(strcmp(currentNode -> username, username) == 0)      //same username inputted
        {
            printf("Username already existed, please try again.\n");
            return;
        }
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
void printTweets(tweetPtr tweetList, char viewingUser[USR_LENGTH])
{
    //to be done
}