#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <sys/wait.h>

char** operation_parser(char *operation);
void execute_pipe(char **my_stdout, char **my_stdin);
int is_background_process(char *operation);
void background_execution(char *operation);
void execute_process(char *operation);
char *parse_string(char *value, char* token);
void pipe_operation_parser(char* operation);
