#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
	
void recent_commands();
void current_directory();
void change_directory(char *path);
void executable_file(char *op);
int find_path(char *path,char *file);
int check_executable(char *filename);
int is_build_in_command(char* operation);
void execute_command(char *operation);
void remove_string(char *string, char *toRemove);
