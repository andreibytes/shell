#include <stdlib.h>
#include <string.h>
#include "environment.h"



int is_environment_var(char* word){
   size_t word_size = strlen(word);

   if(word_size >= 2 && word[0] == '$'){
        return 1;
   }

   return 0;
}

void resolve_environment_var(char** word_p){
    // Start at i = 1 to skip $ and get the size of the environment variable

    size_t env_var_size = 0;

    for(int i = 1; i < strlen(*word_p); i++, env_var_size++);

    char* env_var_name = (char*)malloc(sizeof(char) * env_var_size + 1);

    if(env_var_name == NULL){
            exit(-1);
    }
    
    int k = 0;

    for(int i = 1; i < strlen(*word_p); i++, k++){
       env_var_name[k] = (*word_p)[i];
    }

    env_var_name[k] = '\0';

    char* env_var_value = getenv(env_var_name);

    if(env_var_value != NULL){
        free(*word_p);
        *word_p =  env_var_value;
    }

    free(env_var_name);
}

