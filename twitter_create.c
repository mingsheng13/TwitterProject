//
// Created by chaai on 7/4/2022.
//

#include <stdio.h>
#include <string.h>
#include "twitter_create.h"

void printKeyInfo();

void create_twitter_system(twitter * twitter_system){

    //to be completed
    void(*f[7])(twitter*) = {createUsers,postTweets,followUsers,unfollowUsers,deleteUser,endTurn,endTwitter};
    printKeyInfo();
    twitter_system->num_users = 0;
    twitter_system ->num_tweets = 0;
    size_t choice;
    scanf("%u",&choice);
    fflush(stdin);

    while (choice >=0 && choice <= 6){
        (*f[choice])(twitter_system);

        printKeyInfo();
        scanf("%u",&choice);
        fflush(stdin);
    }
}

void createUsers(twitter* twitter_system){      //create user and prints all available users.
    char username[USR_LENGHT];
    printf("Enter Username: ");
    fgets(username, USR_LENGHT, stdin);     //use fgets to scan string

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