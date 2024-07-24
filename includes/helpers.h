#pragma once

#include <stdio.h>

typedef enum {
    WRITE,
    APPEND,
    READ,
    NOT
} IO_TYPE;

char* file_exists_in_path(char** path, char* file);

char* getword(char* buffer, int* buffer_index);

FILE* open_file_for_redirect(IO_TYPE type, char* path_to_file);
