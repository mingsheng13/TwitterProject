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
void getFollowList(twitter twitter_system, userFollowPtr* currentFollowingList);

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
//    fflush(stdin);
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
    userFollowPtr followingList;
    if(tweetList == NULL)
    {
        puts("No tweets available!\n");
        return;
    }
    else
    {
        getFollowList(*twitter_system, &followingList);
        while(followingList != NULL)
        {
            while(tweetList != NULL)
            {
                if(strcmp(followingList->followerName, tweetList -> user)==0 || strcmp(tweetList -> user, twitter_system -> currentUser)==0)
                {
                    printf("id: %d Author: %s\n%s\n",tweetList -> id, tweetList -> user, tweetList -> msg);
                }
                tweetList = tweetList -> nextPtr;
            }
            followingList = followingList -> nextPtr;
        }
    }
}
// 关注用户出现了一些问题，follower / following 存在bug
void followUsers(twitter* twitter_system)
{
    int y = 0;
    userPtr* userList = &(twitter_system->username);
    userFollowPtr* followingList;
    userFollowPtr* followerList;

    if (strcmp(twitter_system->currentUser, "Not Selected") == 0) {     //select a user before following
        puts("Please select a user before following people.");
        return;
    }
    char followTarget[USR_LENGTH];
    if(printUsers(*twitter_system, 2)== 0)     //use mode 2 to show users that are not being followed by current user
    {
        puts("The code shouls be finished here.");
        return;
    }
    puts("Please enter the user you want to follow:");
    fgets(followTarget, USR_LENGTH, stdin);

    if (followTarget[strlen(followTarget) - 1] == '\n')     //replace the newline char with null char.
        followTarget[strlen(followTarget) - 1] = '\0';

    while(twitter_system -> username != NULL)
    {
        if(strcmp(twitter_system -> username -> username, twitter_system -> currentUser)==0)
        {
            insertFollow(&(twitter_system -> username -> following), followTarget);
            (twitter_system -> username -> num_following) += 1;

        }
        if(strcmp(twitter_system -> username -> username, followTarget)==0)
        {
            insertFollow(&(twitter_system -> username -> follower), twitter_system -> currentUser);
            (twitter_system -> username -> num_followers) += 1;
        }
        twitter_system -> username = twitter_system -> username -> nextPtr;
    }

    twitter_system -> username = *userList;

    //following is not updated because this is passed by value not reference.
//    while(userList != NULL)
//    {
//        if(strcmp(userList -> username, twitter_system -> currentUser)== 0)     //current user
//        {
//            insertFollow(&(userList -> following), followTarget);      //insert follow target's name to current user's following list.
//            (userList -> num_following) += 1;     //current user's following +1
//            puts("added");
//        }
//        if(strcmp(userList -> username, followTarget)==0)       //follow target
//        {
//            insertFollow(&(userList -> follower), twitter_system -> currentUser);
//            (userList -> num_followers) += 1;     //this increase both follower and following(no idea why) //follow target's follower +1
//            puts("added2");
//            y = 1;
//            //insert current user's name into follow target's follower list.
//        }
//        userList = userList -> nextPtr;
//    }


//
//    if(y == 0)
//    {
//        puts("Error username inputted.");
//        return;
//    }
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
    userFollowPtr currentFollowingList;
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
                printf("User: %s; Followers: %d; Following: %d\n" ,userList -> username, userList -> num_followers, userList -> num_followers );
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
                printf("User: %s; Followers: %d; Following: %d\n" ,userList -> username, userList -> num_followers, userList -> num_followers );
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
            getFollowList(twitter_system, &currentFollowingList);    //feed currentFollowingList with the currently selected user's following.
            /*
             *
             * problem here
             *
             * */
            while(userList != NULL)
            {
                if(currentFollowingList == NULL)
                {
                    printf("User: %s; Followers: %d; Following: %d\n" ,userList -> username, userList -> num_followers, userList -> num_followers );
                    y = 1;
                }
                while(currentFollowingList != NULL)
                {
                    if(strcmp(userList -> username, currentFollowingList -> followerName)==0)
                    {
                        currentFollowingList = currentFollowingList -> nextPtr;     //skip followed user
                        puts("debug");
                        continue;
                    }
                    printf("User: %s; Followers: %d; Following: %d\n" ,userList -> username, userList -> num_followers, userList -> num_followers );
                    y = 1;
                    currentFollowingList = currentFollowingList -> nextPtr;
                }
                userList = userList -> nextPtr;
            }
            if(y == 0)
            {
                puts("No user to show");
                return 0;
            }
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

void insertFollow(userFollowPtr* followList, char followName[USR_LENGTH]){
    userFollowPtr previousNode = NULL;
    userFollowPtr currentNode = *followList;
    userFollowPtr newNode = (userFollowPtr) malloc(sizeof(userFollow));

    if(newNode == NULL)
    {
        printf("error allocating memory");
        exit(0);
    }

    strcpy(newNode -> followerName, followName);
    newNode -> nextPtr = NULL;

    while(currentNode != NULL)      //loop to the last place in the list.
    {
        if(strcmp(currentNode -> followerName, followName) == 0)      //same username inputted
        {
            printf("You have already follow this user, please try again.\n");
            return;
        }
        previousNode = currentNode;
        currentNode = currentNode -> nextPtr;       //loop to the next one
    }

    if(previousNode == NULL)        //first one in the list.
    {
        *followList = newNode;
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

void getFollowList(twitter twitter_system, userFollowPtr* currentFollowingList)
{
    userPtr userList = twitter_system.username;
    while(userList != NULL)
    {
        if(strcmp(twitter_system.currentUser, userList -> username)==0)
        {
            *currentFollowingList = userList ->following;     //grab the followerList into a variable
            return;
        }
        userList = userList -> nextPtr;
    }
}