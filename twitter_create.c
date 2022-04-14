//
// Created by chaai on 7/4/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "twitter_create.h"


int printUsers(userPtr userList);       //print all users in the linked list
void printTweets(tweetPtr tweetList, char viewingUser[USR_LENGTH]);
void insertUser(userPtr* userList, char username[USR_LENGTH]);
void insertTweet(tweetPtr* tweetList, char msg[TWEET_LENGTH], int* id, char author[USR_LENGTH]);

void printKeyInfo();

void create_twitter_system(twitter * twitter_system){
    
    strcpy(twitter_system -> currentUser, "Not Selected");      //init. the current user as Not Selected
    twitter_system -> num_users = 0;
    twitter_system -> num_tweets = 0;
    twitter_system -> username = NULL;      //init. the username linked list
    twitter_system -> news_feed = NULL;
    printf("Current user is: %s\n", twitter_system -> currentUser);
    printKeyInfo();
    unsigned int choice;
    scanf("%u", &choice);
    fflush(stdin);

    while (choice >= 0 && choice <= 7){
        switch (choice) {
            case 0:
                createUsers(twitter_system);
                break;
            case 1:
                selectUser(twitter_system);
                break;
            case 2:
                postTweets(twitter_system);
                break;
            case 3:
                followUsers(twitter_system);
                break;
            case 4:
                unfollowUsers(twitter_system);
                break;
            case 5:
                deleteUser(twitter_system);
                break;
            case 6:
                endTurn(twitter_system);
                break;
            case 7:
                endTwitter();
                break;
            default:
                puts("error");
        }
        printf("Current user is: %s\n", twitter_system -> currentUser);
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


    puts("==============================================");
}

void selectUser(twitter * twitter_system){
    userPtr userList = twitter_system -> username;
    char user[USR_LENGTH];
    if(printUsers(userList) == 0)
    {
        return;
    }
    printf("Please enter a user name:\n");
    fgets(user, USR_LENGTH, stdin);     //use fgets to scan string

    if(user[strlen(user)-1] =='\n')     //replace the newline char with null char.
        user [strlen(user)-1] = '\0';

    while (userList != NULL){
        if(strcmp(user,userList -> username) == 0){
            printf("Found the user!\n");
            strcpy(twitter_system -> currentUser,userList -> username);
            return;
        }
        userList = userList -> nextPtr;
    }
    if(userList == NULL)
    {
        if(strcmp(twitter_system -> currentUser, "Not Selected") == 0){
            puts("User not found!");
            return;
        }
    }

}


void postTweets(twitter* twitter_system){

    if(strcmp(twitter_system -> currentUser, "Not Selected") == 0)
    {
        puts("Please select a user before posting tweet");
        return;
    }

    char tweetInput[TWEET_LENGTH];
    puts("Enter your tweet: ");
    fgets(tweetInput,TWEET_LENGTH,stdin);

    if(tweetInput[strlen(tweetInput)-1] =='\n')     //replace the newline char with null char.
        tweetInput[strlen(tweetInput)-1] = '\0';

    insertTweet(&twitter_system -> news_feed,tweetInput,&twitter_system -> num_tweets ,twitter_system -> currentUser);

    twitter_system -> num_tweets += 1;


    puts("Tweet posted successfully!\n");

    printTweets(twitter_system -> news_feed,twitter_system -> username);
}

void followUsers(twitter* twitter_system){
    userPtr userList = twitter_system -> username;

    if(strcmp(twitter_system -> currentUser, "Not Selected") == 0)
    {
        puts("Please select a user before posting tweet");
        return;
    }
    char followTarget[USR_LENGTH];
    puts("Please print the user you want to follow:\n");
//    printUsers(twitter_system -> username);
    fgets(followTarget,USR_LENGTH,stdin);

    if(followTarget[strlen(followTarget)-1] =='\n')     //replace the newline char with null char.
        followTarget [strlen(followTarget)-1] = '\0';

    while (userList != NULL){
        if(strcmp(followTarget,userList -> username) == 0){
            printf("Found the user!\n");
            strcpy(twitter_system -> currentUser,userList -> username);
            return;
        }
        userList = userList -> nextPtr;
    }
    if(userList == NULL)
    {
        if(strcmp(twitter_system -> currentUser, "Not Selected") == 0){
            puts("User not found!");
            return;
        }
    }
//    printf("Test for followUsers success.\n");
}

void unfollowUsers(twitter* twitter_system){
    if(strcmp(twitter_system -> currentUser, "Not Selected") == 0)
    {
        puts("Please select a user before posting tweet");
        return;
    }
    printf("Test for unfollowUsers success.\n");
}

void deleteUser(twitter* twitter_system){
    //link the previous node to next node and use free()
    char username[USR_LENGTH];
    userPtr previousPtr = NULL;
    userPtr currentPtr = twitter_system -> username;

    if(currentPtr == NULL)
    {
        puts("User list is empty!");
        return;
    }

    printUsers(twitter_system -> username);
    printf("Enter the username that you want to delete:");
    fgets(username, USR_LENGTH, stdin);     //use fgets to scan string

    if(username[strlen(username)-1] =='\n')     //replace the newline char with null char.
        username[strlen(username)-1] = '\0';

    if(strcmp(twitter_system -> currentUser, username) == 0)    //if the current user is the currently selected user.
    {
        strcpy(twitter_system -> currentUser, "Not Selected");
    }

    while(currentPtr != NULL && strcmp(currentPtr -> username, username) != 0)      //loop through the list and
    {                                                                               //stop if the username is found
        previousPtr = currentPtr;
        currentPtr = currentPtr -> nextPtr;
    }

    if(currentPtr == NULL)      //if username is not found in the list
    {
        puts("Error username entered! ");
        return;
    }

    if(previousPtr == NULL)     //if the username is the first one in the list
    {
        twitter_system -> username = currentPtr -> nextPtr;
        puts("User deleted.");
    }
    else if(strcmp(currentPtr -> username, username) == 0)
    {
        previousPtr -> nextPtr = currentPtr -> nextPtr;
        free(currentPtr);
        puts("User deleted.");
    }

    //delete user's tweet


}

void endTurn(twitter* twitter_system){
    printf("Test for endTurn success.\n");
}

void endTwitter(){
    printf("Thank you for using.\n");
    exit(0);
}

void printKeyInfo(){
    printf("\n\nEnter the number between 0 and 6:\n");
    printf("Enter 0: Create a user\n");
    printf("Enter 1: Select a user\n");
    printf("Enter 2: Post tweets\n");
    printf("Enter 3: Follow users\n");
    printf("Enter 4: Unfollow users\n");
    printf("Enter 5: delete the user\n");
    printf("Enter 6: End this turn\n");
    printf("Enter 7: End the Twitter system\n");
}

int printUsers(userPtr userList)       //print all users in the linked list
{
    if(userList == NULL)        //the list is empty.
    {
        puts("No user available");
        return 0;
    }
    else
    {
        while(userList != NULL)     //loop through every user in the list
        {
            printf("User: %s; Followers: %d; Following: %d\n" ,userList -> username, userList -> num_followers, userList -> num_followers );
            userList = userList -> nextPtr;
        }
        return 1;
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
    //implement using stack.(first in last out)

    tweetPtr newStack = (tweetPtr)malloc(sizeof(tweet));
    newStack -> id = *id;
    *id = *id + 1;
    strcpy(newStack -> user, author);
    strcpy(newStack -> msg, msg);

    tweetPtr currentStack = *tweetList;
    if(currentStack == NULL)        //first one in the list
    {
        newStack -> nextPtr = NULL;
        *tweetList = newStack;
        return;
    }
    else
    {
        newStack -> nextPtr = currentStack;
        *tweetList = newStack;
    }

}
void printTweets(tweetPtr tweetList, char viewingUser[USR_LENGTH])
{
    //check for following's tweet.strcmp viewingUser's following with
    if(tweetList == NULL){
        puts("No tweets available!\n");
        return;
    }
    else{
        while (tweetList != NULL){
            printf("id: %d Author: %s\n%s\n",tweetList -> id, tweetList -> user, tweetList -> msg);
            tweetList = tweetList -> nextPtr;
        }
    }
}