#include "build_in_commands.h"
#include "queue.h"

/*
 * Function:    recent_commands
 * Purpose:     shows the recent ten commands
 */
void recent_commands()
{
    display();	
}

/*
 * Function:    current_directory
 * Purpose:     prints current directory
 */
void current_directory()
{
    char cwd[PATH_MAX];

    if (getcwd(cwd, sizeof(cwd)) != NULL)
    { 
        printf("%s\n", cwd);
    }
}

/*
 * Function:    change_directory
 * Purpose:     change the directory. If the
 		directory does not exist it 
 		changes directory the path stored 
 		in the $HOME environment variable.
 * In arg:      path: path 
 */
void change_directory(char *path)
{
    if(chdir(path) < 0)
    {
	chdir(getenv("HOME"));
    }
} 

/*
 * Function:    check_executable_file
 * Purpose:     check whether the file is 
 * 		executable
 * In arg:      filename: file name
 * Return val:  0 not executable
 *		1 executable
 */
int check_executable_file(char *filename)
{
    int result;
    struct stat sb;

    result = stat(filename, &sb);

    if (result < 0 || !S_ISREG(sb.st_mode))
    {
	return 0;
    }
    else
    {
	return 1;
    }
}

/*
 * Function:    find_path
 * Purpose:     find out the file path
 * In arg:      path: path
 *		file: file
 * Return val:  0 path found
 *		1 path not found 
 */
int find_path(char *path, char *file)
{
    char *path_enviroment;
    char *begin, *end;
    int stop, found;
    int len;

    if (strchr(file, '/') != NULL) {
  	if (realpath(file, path) == NULL)
        { 
  	    return 0;
	}  	
	return  check_executable_file(path);
    }

    path_enviroment = getenv("PATH");

    if (path_enviroment == NULL || strlen(path_enviroment) <= 0) 
    {
	return 0;
    }

    begin = path_enviroment;
    stop = 0; found = 0;

    while(!stop && !found)
    {
  	end = strchr(begin, ':');
  	if (end == NULL) 
  	{
	    stop = 1;
	    strncpy(path, begin, PATH_MAX);
	    len = strlen(path);
  	} 
  	else 
  	{
	    strncpy(path, begin, end - begin);
	    path[end - begin] = '\0';
	    len = end - begin;
  	}
  	
  	if (path[len - 1] != '/')
	{ 
	    strncat(path, "/", PATH_MAX);
  	}
  	strncat(path, file, PATH_MAX - len);
  	found = check_executable_file(path);
  	
  	if (!stop)
	{ 
	    begin = end + 1;
	}
    } 
  
    return found;
}

/*
 * Function:    is_build_in_command
 * Purpose:     check whether the operation is 
 *		build in command
 * In arg:      operation: operation
 * Return val:  0 not build in command
 *		1 build in command
 */
int is_build_in_command(char* operation)
{
	if( strcmp(operation, "bye") == 0 || strcmp(operation, "dir") == 0 || 
		strstr(operation, "findloc") != NULL || strcmp(operation, "history") == 0 || 
			strstr(operation, "cd") != NULL)
	{
  	    return 1;
	}
	else
	{
	    return 0;	
	}
}

/*
 * Function:    execute_command
 * Purpose:     executes the operation
 * In arg:      operation: operation
 */
void execute_command(char *operation)
{
    if( strcmp(operation, "bye") == 0 )
    {
        exit(0);
    }		
    else if( strcmp(operation, "dir") == 0 )
    {	
	current_directory();
    }
    else if( strstr(operation, "findloc") != NULL )
    {
	char path[PATH_MAX];
	
	remove_string(operation,"findloc ");
	
	if (!find_path(path, operation)) 
	{
	     fprintf(stderr, "%s : is not executable or not existing\n", operation);
	}
	else
	{
	    puts(path);
	}
    }
		
    else if( strcmp(operation, "history") == 0 )
    {
	recent_commands();
    }	
    else if( strstr(operation, "cd") != NULL )
    {
	remove_string(operation,"cd ");
	change_directory(operation);
    }
}

/*
 * Function:    remove_string
 * Purpose:     removes sub string in the string
 * In arg:      string: original string
 *		sub_string: sub string to remove
 */
void remove_string(char *string, char *sub_string)
{
    int len, sub_len;
    int found = 0;

    len = strlen(string);
    sub_len = strlen(sub_string);

    for(int i=0; i<len; i++)
    {
	found = 1;
	for(int j=0; j<sub_len; j++)
	{
	    if(string[i+j] != sub_string[j])
	    {
		found = 0;
		break;
	    }
        }
	if(found == 1)
	{
     	    for(int j=i; j<=len-sub_len; j++)
    	    {
           	string[j] = string[j + sub_len];
    	    }
	    break;
	}
     }
}


