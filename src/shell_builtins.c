#include <stdio.h>
#include <unistd.h>
#include <pwd.h>
#include <string.h>
#include "shell_builtins.h"

void print_shell_prompt(){

    char working_dir[WORKING_DIR_BUFFER_SIZE];
    char* current_working_dir = getcwd(working_dir, WORKING_DIR_BUFFER_SIZE);

    uid_t user_id = getuid();
    struct passwd *pwd;
    pwd = getpwuid(user_id);

    printf("\033[0;36m%s\033[0m:%s $ ", current_working_dir, pwd->pw_name);

}


void change_directory(char* new_dir){

        if(new_dir == NULL){
            return;
        }

        if(strcmp("~", new_dir) == 0){
             char home_dir[255];
             uid_t user_id = getuid();
             struct passwd *pwd;
             pwd = getpwuid(user_id);
             strcat(home_dir, "/home/");
             strcat(home_dir, pwd->pw_name);
             chdir(home_dir);
        } else {
           if(chdir(new_dir) == -1){
                printf("Directory not found\n");
           }
        }
}

