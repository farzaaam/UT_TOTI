
#include "strworks.h"

int main()
{

    int user_number = 1;
    int login = 0;
    int first_run=0;
    user_info *My_users = (user_info *) malloc(sizeof(user_info) * user_number);

    while (1) {


        int index = 0;
        int tedad = 0;
        first_run=1;
        char c = NULL;
        char *cmd;
        cmd = (char *) malloc(sizeof(char));
        int j = 0;
        while (c != '\n') {
            scanf("%c", &c);
            j++;
            if (c != '\n') {
                cmd = realloc(cmd, sizeof(char) * (1 + index));
                cmd[index] = c;
                tedad++;
            }
            index++;
        }
        cmd[index - 1] = '\0';
        /*int** arr = (int**)malloc(r * sizeof(int*));
        for (i = 0; i < r; i++)
        arr[i] = (int*)malloc(c * sizeof(int));*/

        char **tokened = (char **) malloc(3 * sizeof(char *));
        *(tokened) = (char *) malloc(sizeof(char) * 10);
        *(tokened + 1) = (char *) malloc(sizeof(char) * tedad);
        *(tokened + 2) = (char *) malloc(sizeof(char) * (tedad));
        if(*(tokened + 1)==NULL || *(tokened + 2)==NULL ||*(tokened )==NULL) {
            printf("memory error! please try again\n");
            continue;
        }
        int order = tokening(cmd, tokened);
//        free(cmd);
        if (order == 0) {
            printf("unknown order");
            continue;
        }
        if (order == 1) {
            int check = 1;
            for (int i = 1; i < user_number; i++) {
                if (strcmp(*(tokened + 1), My_users[i].username) == 0) {
                    printf("this username already exist");
                    check = 0;
                    continue;
                }
            }
            if (check == 1) {
                user_number++;
                My_users = (user_info *) realloc(My_users, sizeof(user_info) * user_number);
                My_users[user_number - 1].username = (char *) malloc(sizeof(char) * (strlen(*(tokened + 1))));
                My_users[user_number - 1].password = (char *) malloc(sizeof(char) * (strlen(*(tokened + 2))));
                My_users[user_number - 1].username = *(tokened + 1);
                My_users[user_number - 1].password = *(tokened + 2);
                My_users[user_number - 1].user_id = user_number - 1;
                My_users[user_number - 1].posts_number = 0;
                My_users[user_number - 1].user_posts = (post *) malloc(
                        sizeof(post) * (My_users[user_number - 1].posts_number + 1));
                if(My_users[user_number - 1].password==NULL || My_users[user_number - 1].username==NULL ||My_users==NULL || My_users[user_number - 1].user_posts==NULL) {
                    printf("memory error! please try again\n");
                    continue;
                }
                printf("signup successfully\n");
            }
        }
        if (order == 2) {
            login = login_checker(My_users, *(tokened + 2), *(tokened + 1), user_number);
            continue;
        }
        if (order == 3) {
            if (login == 0)
                printf("you are not in any account\n");
            else
                printf("logout successfully\n");
            login = 0;
            continue;
        }
        if (order == 4) {
            if (login == 0) {
                printf("please login to your account\n");
                continue;
            }
            int need_memory = strlen(*(tokened + 1));
            My_users[login].user_posts = (post *) realloc(My_users[login].user_posts,
                                                          (My_users[login].posts_number + 2) * sizeof(post));
            My_users[login].user_posts[My_users[login].posts_number].text = (char *) malloc(
                    (need_memory + 5) * sizeof(char));
            if(My_users[login].user_posts==NULL || My_users[login].user_posts[My_users[login].posts_number].text==NULL) {
                printf("memory error! please try again\n");
                continue;
            }
            strcpy(My_users[login].user_posts[My_users[login].posts_number].text, *(tokened + 1));
            My_users[login].user_posts[My_users[login].posts_number].post_id = My_users[login].posts_number;
            /*My_users[login].user_posts[My_users[login].posts_number].liked_users = (post *) realloc(
                    My_users[login].user_posts[My_users[login].posts_number].liked_users,
                    sizeof(int) * (user_number + 1));
            for (int i = 1; i <= user_number; ++i) {
                My_users[login].user_posts[My_users[login].posts_number].liked_users[i] = 0;
            }*/
            My_users[login].user_posts[My_users[login].posts_number].isexist = 1;
            My_users[login].user_posts[My_users[login].posts_number].like_number=0;
            My_users[login].user_posts = realloc(My_users[login].user_posts,
                                                 sizeof(post) * (My_users[login].posts_number + 1));
            My_users[login].user_posts[My_users[login].posts_number].liked_users=(int *) malloc(sizeof (int)*(user_number+2));
            if(My_users[login].user_posts==NULL) {
                printf("memory error! please try again\n");
                continue;
            }
            My_users[login].posts_number++;
            printf("you post a text successfully\n");
            //continue;
        }
        if (order == 5) {
            if (login == 0) {
                printf("please login to your account\n");
                continue;
            }
            My_users[login].user_posts[atoi(*(tokened + 1))].isexist = 0;
            printf("your post deleted\n");
            continue;
        }
        if (order == 6) {
            if (login == 0) {
                printf("please login to your account\n");
                continue;
            }
            int account = find_user(My_users, *(tokened + 1), user_number);
            if (account != 0) {
                printf("---------------------------\n");
                printf("username:\t%s\n", My_users[account].username);
                show_posts(My_users[account]);
            }
        }
        if (order == 7) {
            if (login == 0) {
                printf("please login to your account\n");
                continue;
            }
            int account = find_user(My_users, My_users[login].username, user_number);
            if (account != 0) {
                printf("---------------------------\n");
                printf("username:\t%s\n", My_users[account].username);
                printf("password:\t%s\n", My_users[account].password);
                show_posts(My_users[account]);
            }
        }
        if (order == 8) {
            if (login == 0) {
                printf("please login to your account\n");
                continue;
            }
            int account = find_user(My_users, *(tokened + 1), user_number);
            if (account != 0) {
                /*My_users[account].user_posts[My_users[account].posts_number].liked_users = (int *) realloc(
                        My_users[account].user_posts[My_users[account].posts_number].liked_users,
                        sizeof(int) * (user_number + 2));*/
                if (My_users[account].user_posts[atoi(*(tokened + 2))].isexist == 1) {

                    for (int i = 1; i <= user_number; ++i) {
                        if (My_users[account].user_posts[atoi(*(tokened + 2))].liked_users[i] != 1)
                            My_users[account].user_posts[atoi(*(tokened + 2))].liked_users[i] = 0;
                    }
                    if(My_users[account].user_posts[atoi(*(tokened + 2))].liked_users[login] == 0)

                        My_users[account].user_posts[atoi(*(tokened + 2))].like_number++;
                    My_users[account].user_posts[atoi(*(tokened + 2))].liked_users[login]=1;
                    printf("you liked this post\n");
                } else
                    printf("this post not exist\n");
            }


        }
//        free(*tokened);
//        free(cmd);
        FILE *accounts= fopen("accounts.txt","w");
        FILE *posts= fopen("posts.txt","w");
        for (int i = 1; i < user_number; ++i) {
            fwrite(My_users[i].username,sizeof(char), strlen(My_users[i].username),accounts);
            fwrite(" ",1,1,accounts);
            fwrite(My_users[i].password,sizeof(char), strlen(My_users[i].password),accounts);
            fwrite(" ",1,1,accounts);
            char * komaki=(char *) malloc(sizeof(char)*10);
            sprintf(komaki,"%d",My_users[i].posts_number);
            fwrite(komaki,1, strlen(komaki),accounts);
            fwrite("\n",1, strlen("\n"),accounts);


            for (int k = 0; k <My_users[i].posts_number ; k++) {
                if(My_users[i].user_posts[k].isexist==1){
                    fwrite(My_users[i].user_posts[k].text,sizeof(char), strlen(My_users[i].user_posts[k].text),posts);
                    fwrite(" ",1,1,posts);
                    fwrite(My_users[i].username,sizeof(char), strlen(My_users[i].username),posts);
                    fwrite(" ",1,1,posts);
                    char* likenumber=(char *) malloc(5*sizeof(char ));
                    sprintf(likenumber,"%d",My_users[i].user_posts[k].like_number);
                    fwrite(likenumber, sizeof(char), strlen(likenumber), posts);
                    fwrite("\n",1, strlen("\n"),posts);

                }

            }
        }
        fclose(accounts);
        fclose(posts);
    }
}