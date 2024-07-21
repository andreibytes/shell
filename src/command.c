#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "helpers.h"
#include "shell_builtins.h"
#include "command.h"

char* program_path[] = {"/usr/local/sbin/", "/usr/local/bin/", "/usr/sbin/", "/usr/bin/", "/sbin/", "/bin/", NULL};

typedef struct {
    char* program;
    char** argv;
    int size_of_argv;
    int capacity_of_argv;
} Command;


void command_argument_append(Command* cmd , char* str);

void command_execute(COMMAND cmd);

COMMAND command_from_buffer(char* buffer){
        Command* command = (Command*)malloc(sizeof(Command));
 
        if(command != NULL){
           int buffer_index = 0;
           command->argv = NULL;
           // Get program name
           command->program = getword(buffer, &buffer_index);
            
            
           // First argument a program expects is its name
           command_argument_append(command, command->program);

           // Append the rest of the arguments
           char* arg_p;
           while((arg_p = getword(buffer, &buffer_index)) != NULL){
                command_argument_append(command, arg_p);
           }

           command_argument_append(command, NULL);         
        }

         
        return (COMMAND)command;
}



void command_argument_append(Command* cmd , char* str){
    if(cmd->argv == NULL){
        cmd->argv = (char**)calloc(5, sizeof(char*));
        if(cmd->argv == NULL){
            exit(-1);
        } else {
            cmd->size_of_argv = 0;
            cmd->capacity_of_argv = 5;
        }
    }


   if(cmd->size_of_argv >= cmd->capacity_of_argv){
        cmd->capacity_of_argv *= 2;
        char** new_argv_p = realloc(cmd->argv, cmd->capacity_of_argv);
        if(new_argv_p == NULL){
            exit(-1);
        }

        cmd->argv = new_argv_p;
    }


    cmd->argv[cmd->size_of_argv] = str;
    cmd->size_of_argv++;
}



void command_execute(COMMAND cmd){
    Command* command = (Command*)cmd;
    
    if(strcmp(command->program, "cd") == 0){
        change_directory(command->argv[1]);
    } else {
            char* path = file_exists_in_path((char**)program_path, command->program);
            if(path != NULL){
                pid_t id = fork();
                if(id != 0){
                    waitpid(id, NULL, 0);
                    free(path);
                } else {
                   execv(path, command->argv);            
                }
            } else {
                    printf("Program not found\n");
            };
    }    
}


void command_destroy(COMMAND cmd){
        
    Command* cmd_p = (Command*)cmd;

    for(int i = 0; i < cmd_p->size_of_argv; i++){
        free(cmd_p->argv + i);
    } 

    free(cmd_p);
}
