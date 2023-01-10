#include <stdio.h>
#include "stdlib.h"
#include "string.h"
struct post {
    char *text;
    int *liked_users;
    int like_number;
    int post_id;
    int isexist;
};
typedef struct post post;
typedef struct users {
    int user_id;
    char *username;
    char *password;
    post *user_posts;
    int posts_number;
};
typedef struct users user_info;


int tokening(char cmd[],char **tokened)
{
    char *cmd_cte;
    cmd_cte=(char *) malloc(sizeof(cmd));
    strcpy(cmd_cte,cmd);
//    *(tokened)=NULL;
//    *(tokened+1)=NULL;
//    *(tokened+2)=NULL;
    *(tokened)=strtok(cmd," ");
    //printf("%s\n",*(tokened));
    *(tokened+1)=strtok(NULL," ");
    //printf("%s\n",*(tokened+1));
    *(tokened+2)=strtok(NULL," ");
    //printf("%s",*(tokened+2));

    if(strcmp(*(tokened),"signup")==0) {
        if(*(tokened+1)!=NULL && *(tokened+2)!=NULL)
            return 1;
    }
    if(strcmp(*(tokened),"login")==0) {
        return 2;
    }
    if(strcmp(*(tokened),"logout")==0) {
        return 3;
    }
    if(strcmp(*(tokened),"post")==0) {
        size_t alloc_size=strlen(cmd_cte)-4;
        //free((tokened+sizeof (tokened)));
        //(tokened+sizeof(tokened))= (char *) realloc((tokened+sizeof(tokened)),alloc_size);
        strcpy(*(tokened+1), &cmd_cte[5]);
        return 4;
    }
    if(strcmp(*(tokened),"delete")==0) {
        return 5;
    }
    if(strcmp(*(tokened),"find_user")==0) {
        return 6;
    }
    if(strcmp(*(tokened),"info")==0) {
        return 7;
    }
    if(strcmp(*(tokened),"like")==0) {
        return 8;
    }
    return 0;
}


void show_posts(user_info My_users)
{
    for (int i = 0; i < My_users.posts_number ; ++i) {
        if(My_users.user_posts[i].isexist==1) {
            printf("---------------------------------------\n");
            printf("post ID:\t%d\n",My_users.user_posts[i].post_id);
            printf("like:\t%d\n",My_users.user_posts[i].like_number);
            printf("text:\t%s\n",My_users.user_posts[i].text);
        }
    }
}

int find_user(user_info My_user[],char username[],int user_number)
{
    if(user_number!=1) {
        for (int i = 1; i < user_number; ++i) {
            if (strcmp(My_user[i].username, username) == 0) {
                printf("user found!\n");
                return i;
            }
        }
    }
    printf("user not found\n");
    return 0;
}



int login_checker(user_info My_user[], char password[], char username[], int user_number)
{
    for (int i = 1; i <= user_number; ++i) {
        if (strcmp(My_user[i].username, username) == 0) {
            if (strcmp(My_user[i].password, password) == 0) {
                printf("login successfully\n");
                return i;
            } else {
                printf("wrong password\n");
                return 0;
            }
        }
    }
    printf("user not found\n");
    return 0;
}
