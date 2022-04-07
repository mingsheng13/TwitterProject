//
// Created by chaai on 7/4/2022.
//

#include <stdio.h>
#include <string.h>
#include "twitter_create.h"

void create_twitter_system(twitter * twitter_system){

    //to be completed
    char username[USR_LENGHT];
    printf("Enter Username: ");
    scanf("%s", username);
    strcpy(twitter_system->users[0].username,username);

    twitter_system-> users[0].num_followers = 0;
    twitter_system->users[0].num_following = 0;
}