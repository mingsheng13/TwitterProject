//
// Created by chaai on 7/4/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "twitter_create.h"

int printUsers(twitter twitter_system, int mode);       //print all users in the linked list
void printTweets(tweetPtr tweetList, char viewingUser[USR_LENGTH]);
void insertUser(userPtr* userList, char username[USR_LENGTH]);
void insertFollow(userFollowPtr* followList, char followName[USR_LENGTH]);
void insertTweet(tweetPtr* tweetList, char msg[TWEET_LENGTH], int* id, char author[USR_LENGTH]);
char** getFollowList(twitter twitter_system, int *following);

void printKeyInfo();

void create_twitter_system(twitter * twitter_system){
    strcpy(twitter_system -> currentUser, "Not Selected");      //init. the current user as Not Selected
    twitter_system -> num_users = 0;
    twitter_system -> num_tweets = 0;
    twitter_system -> username = NULL;      //init. the username linked list
    twitter_system -> news_feed = NULL;
    //printf("Current user is: %s\n", twitter_system -> currentUser);
    printKeyInfo();
    size_t choice;
    printf("? ");
    scanf("%zu", &choice);
    getchar();      //clear input buffer

    while (choice >= 0 && choice <= 8){
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
                getNewsFeed(twitter_system);
                break;
            case 4:
                followUsers(twitter_system);
                break;
            case 5:
                unfollowUsers(twitter_system);
                break;
            case 6:
                deleteUser(twitter_system);
                break;
            case 7:
                endTurn(twitter_system);
                break;
            case 8:
                endTwitter();
                break;
            default:
                puts("error");
        }
        printf("Current user is: %s\n", twitter_system -> currentUser);
        printKeyInfo();
        printf("? ");
        scanf("%zu",&choice);
//        fflush(stdin);
        getchar();  //clear input buffer
    }
}

void createUsers(twitter* twitter_system){      //create user and prints all available users.
    char username[USR_LENGTH];
    printf("Enter Username: \n");
    fgets(username, USR_LENGTH, stdin);     //use fgets to scan string

    if(username[strlen(username)-1] =='\n')     //replace the newline char with null char.
        username[strlen(username)-1] = '\0';

    insertUser(&twitter_system -> username, username);      //insert username into linkedList
    twitter_system -> num_users += 1;

    printUsers(*twitter_system, 0);


    puts("==============================================");
}

void selectUser(twitter * twitter_system){
    userPtr userList = twitter_system -> username;
    char user[USR_LENGTH];
    if(printUsers(*twitter_system, 1) == 0)     //printUser return 0 if the list is empty
        return;

    printf("Please enter a user name:\n");
    fgets(user, USR_LENGTH, stdin);     //use fgets to scan string

    if(user[strlen(user)-1] =='\n')     //replace the newline char with null char.
        user[strlen(user)-1] = '\0';

    while (userList != NULL){
        if(strcmp(user,userList -> username) == 0){
            //printf("Found the user!\n");
            strcpy(twitter_system -> currentUser,userList -> username);     //change the current user
            return;
        }
        userList = userList -> nextPtr;
    }
    if(strcmp(twitter_system -> currentUser, "Not Selected") == 0){     //if the current user is still not selected
        puts("User not found!");
        return;
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



    puts("Tweet posted successfully!\n");

    printTweets(twitter_system -> news_feed,twitter_system -> currentUser);
}

void getNewsFeed(twitter* twitter_system){      //done
    tweetPtr tweetList = twitter_system -> news_feed;
    char** followingList;
    int following;
    if(tweetList == NULL)
    {
        puts("No tweets available!\n");
        return;
    }
    else
    {
        /*
         * problem here
         * need to loop through linked list over and over again
         * not sure how to do that.
         */
//        followingList = getFollowList(*twitter_system, &following);
//        for(int i = 0; i < following; i++)
//        {
//            while(tweetList != NULL)
//            {
//                if(strcmp(followingList->followName, tweetList -> user) == 0 || strcmp(tweetList -> user, twitter_system -> currentUser) == 0)
//                {
//                    printf("id: %d Author: %s\n%s\n",tweetList -> id, tweetList -> user, tweetList -> msg);
//                }
//                tweetList = tweetList -> nextPtr;
//            }
//            followingList = followingList -> nextPtr;
//        }
    }
}
// 关注用户出现了一些问题，follower / following 存在bug
void followUsers(twitter* twitter_system)
{
    userPtr user = twitter_system -> username;

    if (strcmp(twitter_system->currentUser, "Not Selected") == 0) {     //select a user before following
        puts("Please select a user before following people.");
        return;
    }
    char followTarget[USR_LENGTH];
    if(printUsers(*twitter_system, 2)== 0)     //use mode 2 to show users that are not being followed by current user
    {
        puts("No one to follow");
        return;
    }
    puts("Please enter the user you want to follow:");
    fgets(followTarget, USR_LENGTH, stdin);

    if (followTarget[strlen(followTarget) - 1] == '\n')     //replace the newline char with null char.
        followTarget[strlen(followTarget) - 1] = '\0';

    while(user != NULL)
    {
        if(strcmp(user -> username, twitter_system -> currentUser) == 0)
        {
            strcpy(user -> following[user -> num_following], followTarget);
            user -> num_following += 1;
        }
        if(strcmp(user -> username, followTarget) == 0)
        {
            strcpy(user -> follower[user -> num_followers], twitter_system -> currentUser);
            user -> num_followers += 1;
        }
        user = user -> nextPtr;
    }
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

    printUsers(*twitter_system, 0);
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
    printf("End turn. Please select another user.\n");
    strcpy(twitter_system -> currentUser, "Not Selected");
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
    printf("Enter 3: News feed\n");
    printf("Enter 4: Follow users\n");
    printf("Enter 5: Unfollow users\n");
    printf("Enter 6: delete the user\n");
    printf("Enter 7: End this turn\n");
    printf("Enter 8: End the Twitter system\n");
}

int printUsers(twitter twitter_system, int mode){       //print all users in the linked list
    userPtr userList = twitter_system.username;

    if(userList == NULL)        //the list is empty.
    {
        puts("No user available");
        return 0;
    }
    else
    {
        if(mode == 0)
        {
            while(userList != NULL)     //loop through every user in the list
            {
                printf("User: %s; Followers: %d; Following: %d\n" ,userList -> username, userList -> num_followers, userList -> num_following );
                userList = userList -> nextPtr;
            }
        }
        else if(mode == 1)      //print user without current user.
        {
            int y = 0;
            while(userList != NULL)
            {
                if(strcmp(userList -> username, twitter_system . currentUser) == 0 )
                {
                    userList = userList -> nextPtr;
                    continue;
                }
                printf("User: %s; Followers: %d; Following: %d\n" ,userList -> username, userList -> num_followers, userList -> num_following );
                y = 1;
                userList = userList -> nextPtr;
            }
            if(y == 0)
            {
                puts("No user to show");
                return 0;
            }
        }
        else if(mode == 2)      //print user without current user and following user.
        {
            int y = 0;
            char **followList;
            int following;
            followList = getFollowList(twitter_system, &following);

            if(followList == NULL)
            {
                printUsers(twitter_system, 1);
                return 1;
            }
            /*
             * Problem here
             * username still showing even after following user.
             */
            while(userList != NULL)
            {
                for(int i = 0; i < following; i++)
                {
                    if((strcmp(followList[i], userList -> username) == 0) || (strcmp(userList -> username, twitter_system.currentUser) == 0))
                    {
                        break;
                    }
                    printf("User: %s; Followers: %d; Following: %d\n" ,userList -> username, userList -> num_followers, userList -> num_following);
                }
                userList = userList -> nextPtr;
            }
//            if(y == 0)
//            {
//                puts("No user to show");
//                return 0;
//            }
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
        exit(1);
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

//void insertFollow(userFollowPtr* followList, char followName[USR_LENGTH]){
//    userFollowPtr previousNode = NULL;
//    userFollowPtr currentNode = *followList;
//    userFollowPtr newNode = (userFollowPtr) malloc(sizeof(userFollow));
//
//    if(newNode == NULL)
//    {
//        printf("error allocating memory");
//        exit(0);
//    }
//
//    strcpy(newNode -> followName, followName);
//    newNode -> nextPtr = NULL;
//
//    while(currentNode != NULL)      //loop to the last place in the list.
//    {
//        if(strcmp(currentNode -> followName, followName) == 0)      //same username inputted
//        {
//            printf("You have already follow this user, please try again.\n");
//            return;
//        }
//        previousNode = currentNode;
//        currentNode = currentNode -> nextPtr;       //loop to the next one
//    }
//
//    if(previousNode == NULL)        //first one in the list.
//    {
//        *followList = newNode;
//    }
//    else
//    {
//        previousNode -> nextPtr = newNode;      //points the previous node's pointer to the new node.
//    }
//}

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
    if(tweetList == NULL)
    {
        puts("No tweets available!\n");
        return;
    }
    else
    {
        while (tweetList != NULL)
        {
            printf("id: %d Author: %s\n%s\n",tweetList -> id, tweetList -> user, tweetList -> msg);
            tweetList = tweetList -> nextPtr;
        }
    }
}

char** getFollowList(twitter twitter_system, int * following)       //function for returning current user's following list
{
    userPtr userList = twitter_system.username;
    while(userList != NULL)
    {
        if(strcmp(twitter_system.currentUser, userList -> username)==0)
        {
            char **arr = (char**)malloc(userList -> num_following * sizeof(char*));     //allocate rows
            for(int i = 0; i < userList -> num_following; i++)
            {
                arr[i] = (char*)malloc(USR_LENGTH * sizeof(char));      //allocate columns
            }
            for(int i = 0; i < userList -> num_following; i++)
            {
                strcpy(arr[i], userList -> following[i]);       //put the list into new array
            }
            *following = userList -> num_following;

            if(userList -> num_following == 0)
                return arr = NULL;

            return arr;     //return the array
        }
        userList = userList -> nextPtr;
    }
}