#include <stdio.h>
#include <stdlib.h>
#include "shell_builtins.h"
#include "command.h"

int main(int argc, char* argv[]){
        char* command_buffer = NULL;
        size_t command_size = 0;
        ssize_t chars_read;

        while(1){

            print_shell_prompt();
            
            chars_read = getline(&command_buffer, &command_size, stdin);

            if(chars_read < 0){
                    printf("Error occured, try again\n");
                    continue;
            }
            
            COMMAND command = command_from_buffer(command_buffer);
            if(command == NULL) {
                printf("Command failed\n");
            } else {
                command_execute(command);
                free(command);
            }            
            
            free(command_buffer);
            command_buffer = NULL;
            
        }


        return 0;
}
