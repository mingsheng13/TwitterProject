//
// Created by chaai on 7/4/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "twitter_create.h"

int printUsers(twitter twitter_system, int mode);       //print all users in the linked list
void insertUser(userPtr* userList, char username[USR_LENGTH]);
void insertTweet(tweetPtr* tweetList, char msg[TWEET_LENGTH], int* id, char author[USR_LENGTH]);
char** getFollowList(twitter twitter_system, int *following);
int userIsAvailable(twitter twitter_system, char target[USR_LENGTH]);

void printKeyInfo();
void welcomeGuide();

void create_twitter_system(twitter * twitter_system){
    strcpy(twitter_system -> currentUser, "Not Selected");      //init. the current user as Not Selected
    twitter_system -> num_users = 0;
    twitter_system -> num_tweets = 0;
    twitter_system -> username = NULL;      //init. the username linked list
    twitter_system -> news_feed = NULL;
    //printf("Current user is: %s\n", twitter_system -> currentUser);
    welcomeGuide();
    printKeyInfo();
    size_t choice;
    printf("Your choice: ");
    scanf("%zu", &choice);
    getchar();      //clear input buffer
    printf("------------------------------------------------------------------------------->\n\n");
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
        printf("Your choice: ");
        scanf("%zu",&choice);
//        fflush(stdin);
        getchar();  //clear input buffer
        printf("------------------------------------------------------------------------------->\n\n");
    }
}

void welcomeGuide(){
    printf("================================================================================\n");
    printf("Copyright (C) Xinyuan He and Ming Sheng Chai Corporation. All rights reserved.\n");
    printf("Check the terminal...\n");
    printf("Check the linked list...\n");
    printf("Twitter system build up success!\n");
    printf("Welcome to the Twitter system!\n");
    printf("================================================================================\n");
}

void createUsers(twitter* twitter_system){      //create user and prints all available users.
    char username[USR_LENGTH];
    printf("Please enter Username: \n");
    fgets(username, USR_LENGTH, stdin);     //use fgets to scan string

    if(username[strlen(username)-1] =='\n')     //replace the newline char with null char.
        username[strlen(username)-1] = '\0';

    insertUser(&twitter_system -> username, username);      //insert username into linkedList
    twitter_system -> num_users += 1;
    printf("User create successful!\n");
    printUsers(*twitter_system, 0);


//    puts("==============================================");
}

void selectUser(twitter * twitter_system){
    userPtr userList = twitter_system -> username;
    char user[USR_LENGTH];
    if(printUsers(*twitter_system, 1) == 0)     //printUser return 0 if the list is empty
        return;

    printf("Please enter a user name:\n");
    fgets(user, USR_LENGTH, stdin);     //use fgets to scan string
    printf("------------------------------------------------------------------------------->\n\n");

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
    printf("------------------------------------------------------------------------------->\n\n");

    if(tweetInput[strlen(tweetInput)-1] =='\n')     //replace the newline char with null char.
        tweetInput[strlen(tweetInput)-1] = '\0';

    insertTweet(&twitter_system -> news_feed,tweetInput,&twitter_system -> num_tweets ,twitter_system -> currentUser);
    puts("Tweet posted successfully!\n");
}

void getNewsFeed(twitter* twitter_system){      //done
    int check = 0;
    tweetPtr tweetList = twitter_system -> news_feed;
    int numFollowing;
    char** followingList = getFollowList(*twitter_system, &numFollowing);

    if(strcmp(twitter_system -> currentUser, "Not Selected") == 0)
    {
        puts("Please select a user before reading tweets");
        return;
    }

    if(tweetList == NULL)
    {
        puts("No tweets available!\n");
        return;
    }

    while(tweetList != NULL)
    {
        if(numFollowing == 0)       //if user is not following anyone, print he's own tweet only.
        {
            if(strcmp(tweetList -> user, twitter_system -> currentUser)==0)
            {
                printf("id: %d\n%s says: \n%s\n\n",tweetList -> id, tweetList -> user, tweetList -> msg);
                check = 1;
            }
            tweetList = tweetList -> nextPtr;
            continue;
        }
        else
        {
            for(int i = 0; i < numFollowing; i++)       //only print following users' tweet and self's tweet
            {
                if(strcmp(followingList[i], tweetList -> user)!=0 || strcmp(tweetList -> user, twitter_system ->currentUser)!=0)
                {
                    printf("id: %d\n%s says: \n%s\n\n",tweetList -> id, tweetList -> user, tweetList -> msg);
                    check = 1;
                    break;
                }
            }
            tweetList = tweetList -> nextPtr;
        }
    }
    if(check == 0)      //if check == 0, means it's not printing anything.
    {
        puts("no tweet available");
        return;
    }
}

void followUsers(twitter* twitter_system)
{
    int num_following;
    char **followList = getFollowList(*twitter_system, &num_following);
    userPtr user = twitter_system -> username;

    if (strcmp(twitter_system->currentUser, "Not Selected") == 0) {     //select a user before following
        puts("Please select a user before following people.");
        return;
    }
    char followTarget[USR_LENGTH];
    if(printUsers(*twitter_system, 2) == 0)     //use mode 2 to show users that are not being followed by current user
    {
//        puts("No one to follow");
        return;
    }
    puts("Please enter the user you want to follow:");
    fgets(followTarget, USR_LENGTH, stdin);
    printf("------------------------------------------------------------------------------->\n\n");

    if (followTarget[strlen(followTarget) - 1] == '\n')     //replace the newline char with null char.
        followTarget[strlen(followTarget) - 1] = '\0';

    if(!userIsAvailable(*twitter_system, followTarget))
    {
        puts("User not found!");
        return;
    }

    if(strcmp(twitter_system -> currentUser, followTarget)==0)
    {
        puts("You cannot follow yourself.");
        return;
    }

    for(int i = 0; i < num_following; i++)
    {
        if(strcmp(followList[i], followTarget) == 0)        //check for duplicate follow
        {
            puts("You cannot follow this person.");
            return;
        }
    }

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
            printf("Successfully followed user '%s'\n", followTarget);
        }
        user = user -> nextPtr;
    }
}

void unfollowUsers(twitter* twitter_system){
    userPtr user = twitter_system -> username;
    char unfollowTarget[USR_LENGTH];
    char** followingList;
    int numFollowing;
    int swapStart;
    int check = 0;
    if(strcmp(twitter_system -> currentUser, "Not Selected") == 0)
    {
        puts("Please select a user before unfollowing user.");
        return;
    }

    followingList = getFollowList(*twitter_system, &numFollowing);
    for(int i = 0; i < numFollowing; i++)
    {
        printf("Username: %s\n", followingList[i]);
        check = 1;
    }
    if(check == 0)
    {
        puts("No user to unfollow.");
        return;
    }



    puts("Please enter the user you want to unfollow:");
    fgets(unfollowTarget, USR_LENGTH, stdin);
    printf("------------------------------------------------------------------------------->\n\n");

    if (unfollowTarget[strlen(unfollowTarget) - 1] == '\n')     //replace the newline char with null char.
        unfollowTarget[strlen(unfollowTarget) - 1] = '\0';

    if(!userIsAvailable(*twitter_system, unfollowTarget))
    {
        puts("User not found!");
        return;
    }

    if(strcmp(twitter_system -> currentUser, unfollowTarget)==0)
    {
        puts("You cannot unfollow yourself!");
        return;
    }

    while(user != NULL)
    {
        if(strcmp(user -> username, twitter_system -> currentUser)==0)      //remove target from current user's following list
        {
            swapStart = 0;
            for(int i = 0; i < numFollowing; i++)
            {
                if(strcmp(user -> following[i], unfollowTarget)==0)
                {
                    swapStart = 1;
                }
                if(swapStart == 1 && user->num_following == 1)
                {
                    strcpy(user -> following[0], "\0");
                }
                else if(swapStart == 1 && i != numFollowing - 1)     //deletion of array.
                {
                    strcpy(user -> following[i], user -> following[i+1]);
                }
            }
            user -> num_following -= 1;
        }
        if(strcmp(user -> username, unfollowTarget)==0)     //remove current user from target's follower list.
        {
            swapStart = 0;
            for(int i = 0; i < user -> num_followers; i++)
            {
                if(strcmp(user -> follower[i], twitter_system -> currentUser)==0)
                {
                    swapStart = 1;
                }
                if(swapStart == 1 && user -> num_followers == 1)
                {
                    strcpy(user -> follower[0], "\0");
                }
                else if(swapStart == 1 && i != (user -> num_followers - 1))
                {
                    strcpy(user -> follower[i], user -> follower[i+1]);
                }
            }
            user -> num_followers -= 1;
        }
        user = user -> nextPtr;
    }
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
    printf("------------------------------------------------------------------------------->\n\n");

    if(username[strlen(username)-1] =='\n')     //replace the newline char with null char.
        username[strlen(username)-1] = '\0';

    if(!userIsAvailable(*twitter_system, username))
    {
        puts("Invalid username entered");
        return;
    }


    /*
     * ===============================================
     * remove user from every following & follower list
     * ===============================================
     */

    userPtr remFollowing = twitter_system -> username;
    int swapStart;
    while(remFollowing != NULL)
    {
        swapStart = 0;
        for(int i = 0; i < remFollowing -> num_following; i++)
        {
            if(strcmp(remFollowing -> following[i], username) == 0)
            {
                swapStart = 1;
            }
            if(swapStart == 1 && remFollowing -> num_following == 1)        //only one in the list
            {
                strcpy(remFollowing -> following[0], "\0");
            }
            else if(swapStart == 1 && i != remFollowing -> num_following - 1)
            {
                strcpy(remFollowing -> following[i] , remFollowing -> following[i + 1]);
            }
        }
        if(swapStart == 1)
        {
            remFollowing -> num_following -= 1;
        }


        remFollowing = remFollowing -> nextPtr;
    }

    //remove current user from every user's following list

    userPtr remFollowers = twitter_system -> username;
    while(remFollowers != NULL)
    {
        swapStart = 0;
        for(int i = 0; i< remFollowers -> num_followers; i++)
        {
            if(strcmp(remFollowers -> follower[i], username)==0)
            {
                swapStart = 1;
            }
            if(swapStart == 1 && remFollowers -> num_followers == 1)
            {
                strcpy(remFollowers -> follower[0], "\0");
            }
            else if(swapStart == 1 && i != remFollowers -> num_followers -1)
            {
                strcpy(remFollowers -> follower[i], remFollowers -> follower[i+1]);
            }
        }
        if(swapStart == 1)
            remFollowers -> num_followers -= 1;
        remFollowers = remFollowers -> nextPtr;
    }

    /*
     * ===============================
     * remove user from username list.
     * ===============================
     */

    if(strcmp(twitter_system -> currentUser, username) == 0)    //if the current user is the currently selected user.
    {
        strcpy(twitter_system -> currentUser, "Not Selected");
    }

    while(currentPtr != NULL && strcmp(currentPtr -> username, username) != 0)      //loop through the list and
    {                                                                               //stop if the username is found
        previousPtr = currentPtr;
        currentPtr = currentPtr -> nextPtr;
    }

    if(previousPtr == NULL)     //if the username is the first one in the list
    {
        userPtr tmp = twitter_system -> username;
        twitter_system -> username = currentPtr -> nextPtr;
        free(tmp);
        puts("User deleted.");
    }
    else if(strcmp(currentPtr -> username, username) == 0)
    {
        previousPtr -> nextPtr = currentPtr -> nextPtr;
        free(currentPtr);
        puts("User deleted.");
    }

    /*
     * ===================
     * delete user's tweet
     * ===================
     */


    tweetPtr currentTweetPtr = twitter_system -> news_feed;
    tweetPtr previousTweetPtr = NULL;

    if(currentTweetPtr == NULL)
    {
        return;
    }

    //first in the list
    while(currentTweetPtr != NULL && strcmp(currentTweetPtr -> user, username) == 0)    //if the tweet to delete is at the front
    {
        previousTweetPtr = currentTweetPtr;
        twitter_system -> news_feed = currentTweetPtr -> nextPtr;
        currentTweetPtr = twitter_system -> news_feed;
        free(previousTweetPtr);
    }

    while(currentTweetPtr != NULL)      //if it's not at the front
    {
        if(strcmp(currentTweetPtr -> user, username)==0)
        {
            previousTweetPtr -> nextPtr = currentTweetPtr -> nextPtr;
            free(currentTweetPtr);
            currentTweetPtr = previousTweetPtr;
        }
        previousTweetPtr = currentTweetPtr;
        currentTweetPtr = currentTweetPtr -> nextPtr;
    }

}

void endTurn(twitter* twitter_system){
    printf("End turn. Please select another user.\n");
    strcpy(twitter_system -> currentUser, "Not Selected");
}

void endTwitter(){
    printf("Thank you for using.\n");
    printf("================================================================================");
    exit(0);
}

void printKeyInfo(){
    printf("================================================================================\n");
    printf("\n============================== M A I N     M E N U =============================\n");
    printf("Enter the number between 0 and 6:                                                    \n");
//    printf("                                                                                     \n");
    printf("Enter 0: Create a user                              **                                  \n");
    printf("Enter 1: Select a user                           **                                    \n");
    printf("Enter 2: Post tweets                           **                                      \n");
    printf("Enter 3: News feed                          **                                         \n");
    printf("Enter 4: Follow users                     **    ***********************************    \n");
    printf("Enter 5: Unfollow users                     **                                        \n");
    printf("Enter 6: delete the user                       **                                       \n");
    printf("Enter 7: End this turn                           **                                     \n");
    printf("Enter 8: End the Twitter system                     **                                   \n");
    printf("\n================================================================================\n\n");
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
            int bool;
            int y = 0;
            char **followList;
            int following;
            followList = getFollowList(twitter_system, &following);

            if(followList == NULL)      //if current user is not following anyone, return printUser function with mode 1;
            {
                return printUsers(twitter_system, 1);
            }

            while(userList != NULL)
            {
                bool = 0;
                for(int i = 0; i < following; i++)
                {
                    if((strcmp(followList[i], userList -> username) == 0) || (strcmp(userList -> username, twitter_system.currentUser) == 0))   //find if the target is already in the following list.
                    {
                        bool = 1;
                        break;
                    }
                }
                if(bool == 0)       //print the username if it's not in the following list.
                {
                    printf("User: %s; Followers: %d; Following: %d\n" ,userList -> username, userList -> num_followers, userList -> num_following);
                    y = 1;
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
        printf("error allocating memory\n");
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

void insertTweet(tweetPtr* tweetList, char msg[TWEET_LENGTH], int* id, char author[USR_LENGTH])
{
    //implement using stack.(first in last out)

    tweetPtr newStack = (tweetPtr)malloc(sizeof(tweet));
    newStack -> id = *id;
    *id = *id + 1;      //increment the tweet's id
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
    return NULL;
}

int userIsAvailable(twitter twitter_system, char target[USR_LENGTH])
{
    userPtr userList = twitter_system . username;
    while(userList != NULL)
    {
        if(strcmp(userList -> username, target) == 0)
            return 1;
        userList = userList -> nextPtr;
    }
    return 0;
}

