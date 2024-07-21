#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "helpers.h"
#include "shell_builtins.h"


char* file_exists_in_path(char** path, char* file){
    int path_index = 0;
    char* absolute_program_path = NULL;

    // Check current path first
    char working_dir_buf[WORKING_DIR_BUFFER_SIZE];
    char* working_dir = getcwd(working_dir_buf, WORKING_DIR_BUFFER_SIZE);
     if(working_dir != NULL){
        size_t working_dir_size = strlen(working_dir);
        size_t file_size = strlen(file);
        char* path_p = (char*)calloc(working_dir_size + file_size + 2, sizeof(char));

        if(path_p == NULL){
            exit(-1);
        } 

        path_p = strcat(path_p, working_dir);
        path_p = strcat(path_p, "/");
        path_p = strcat(path_p, file);

        if(access(path_p, F_OK) == 0){
            absolute_program_path = path_p;
            return absolute_program_path;
        }
     }
    

    while(path[path_index] != NULL){
        size_t path_size = strlen(path[path_index]);
        size_t file_size = strlen(file);
        char* path_p = (char*)calloc(path_size + file_size + 1, sizeof(char));

        if(path_p == NULL){
            exit(-1);
        }


        path_p = strcat(path_p, path[path_index]);
        path_p = strcat(path_p, file);


        if(access(path_p, F_OK) == 0){
            absolute_program_path = path_p;
            break;
        } else {
                free(path_p);
        }

        path_index++;
    }


    return absolute_program_path;
}



char* getword(char* buffer, int* buffer_index){

    // Check we haven't reached the end of the buffer
    
    if(buffer[*buffer_index] == '\n' || buffer[*buffer_index] == '\0'){
        return NULL;
    }
    
    // We haven't reached the end of the buffer, so clear leading spaces

    while(buffer[*buffer_index] == ' '){
         *buffer_index += 1;
    }

    // Get size of word
    int  word_size = 0;
    
    int old_index = *buffer_index;

    while(buffer[*buffer_index] != ' ' && buffer[*buffer_index] != '\n' && buffer[*buffer_index] != '\0'){
        word_size++;
        *buffer_index += 1;
    }

    *buffer_index = old_index;

    // Dynamically allocate a buffer for the word that also includes a null-terminator
    char* word_buf_p = (char*)malloc(sizeof(char) * (word_size + 1));
    if(word_buf_p == NULL){
        exit(-1);
    }

    // Copy over the word
    int word_buf_i = 0;
    while(buffer[*buffer_index] != ' ' && buffer[*buffer_index] != '\n' && buffer[*buffer_index] != '\0'){
        word_buf_p[word_buf_i] = buffer[*buffer_index];
        word_buf_i++;
        *buffer_index += 1;
    }

    word_buf_p[word_size] ='\0';
    return word_buf_p;
 }
