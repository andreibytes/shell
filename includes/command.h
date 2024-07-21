#pragma once

typedef void* COMMAND;


COMMAND command_from_buffer(char* buffer);

void command_execute(COMMAND cmd);

void command_destroy(COMMAND cmd);
