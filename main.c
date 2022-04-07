#include <stdio.h>
#include "twitter_create.h"


int main() {

    twitter twitter_system;
    create_twitter_system(&twitter_system);
    printf("Username: %s\n",twitter_system.users[0].username);
    printf("Followers: %d\n",twitter_system.users[0].num_followers);
    printf("Following: %d\n",twitter_system.users[0].num_following);

//    for(int i =0; i < twitter_system.num_users; i++){
//        user usr = twitter_system.users[i];
//        printf("User: %s; Followers: %d; Following: %d\n",usr.username, usr.num_followers, usr.num_followers );
//    }
    //This is a print to show all the information when creating the users
    return 0;
    //implement here the code to print the users
    // for each user you need to print the username, the number of followers and the number of users that the current user is following




}
