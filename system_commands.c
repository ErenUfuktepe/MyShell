#include "system_commands.h" 
#include "build_in_commands.h"

/*
 * Function:    parse_string
 * Purpose:     parses given string
 * In arg:      value: string to parse
 *		token: parsing character
 * Return val:  parsed string
 */
char *parse_string(char *value, char* token)
{
	char *pch = strtok(value, token);
	
	while(pch != NULL)
	{
		value = pch;
		pch =strtok(NULL,token);
	}

	return value;
}

/*
 * Function:    is_background_process
 * Purpose:     checks whether the operation is
 *		background process or not
 * In arg:      operation: operation
 * Return val:  1 background process
 *		0 not background process
 */
int is_background_process(char *operation)
{
	int len = strlen(operation);
	char *ch = "&";
	
	if(operation[len-1] == ch[0])
		return 1;
	return 0;
}

/*
 * Function:    background_execution
 * Purpose:     executes background process
 * In arg:      operation: operation
 */
void background_execution(char *operation)
{
	pid_t child = fork();
			
	remove_string(operation,"&");
			
	if( child < 0 )
	{
		perror("Error occurred...\n");
		exit(-1);
	}
	else if( child == 0 )
	{
		if( strstr(operation, "|") != NULL)
			pipe_operation_parser(operation);
		execvp(operation_parser(operation)[0],operation_parser(operation));	
	}
	else if( child > 0 ){ }
}


/*
 * Function:    execute_process
 * Purpose:     executes process
 * In arg:      operation: operation
 */
void execute_process(char *operation)
{
	pid_t child = fork();
	
	if( child < 0 )
	{
		perror("Error occurred...\n");
		exit(-1);
	}
	else if( child == 0 )
	{
		if( strstr(operation, "|") != NULL)
			pipe_operation_parser(operation);
					
		execvp(operation_parser(operation)[0],operation_parser(operation));	
	}
	else if( child > 0 )
		wait(NULL);

	wait(NULL);	
}

/*
 * Function:    operation_parser
 * Purpose:     removes the spaces in the 
 *		given operation
 * In arg:      operation: operation
 * Return val:  string without spaces
 */
char** operation_parser(char *operation)
{
  	char * pch;
	char **argv= malloc(sizeof(char**));
	int count = 0;
	pch = strtok (operation," ");
	
	while (pch != NULL)
	{
		argv[count] = pch;
		pch = strtok (NULL, " ");
		count++;
	}
	
	argv[count] = NULL;

	return argv;
}

/*
 * Function:    pipe_operation_parser
 * Purpose:     to send the output of one command
 *		to another command for further processing.
 * In arg:      my_stdout: pipe out		
 *		my_stdin: pipe in
 */
void execute_pipe(char **my_stdout, char **my_stdin)
{
	pid_t pid;

	int fd[2];
	int return_value = pipe(fd);
	
	if(return_value == -1)
	{
		perror("Something is wronge with my pipe...");
		exit(1);
	}
	pid =fork();
	
	if( pid == 0)
	{
		close(1);// closing normal stdout 
		dup(fd[1]);// making stdout same as fd[1] 
		close(fd[0]); 
		execvp(my_stdout[0],my_stdout); 	
	}

	else if(pid > 0)
	{
        	close(0);// closing normal stdin 
        	dup(fd[0]);// making stdin same as fd[0]
		close(fd[1]);   	
		execvp(my_stdin[0],my_stdin);
	}
	
	else
	{ 
		perror("Error occurred...\n");
		exit(-1);
	}
}

/*
 * Function:    pipe_operation_parser
 * Purpose:     parse the operation in order to
 *		use pipe.
 * In arg:      operation: operation
 */
void pipe_operation_parser(char* operation)
{	
	char **op = malloc(sizeof(char**));
	char **my_stdout = malloc(sizeof(char**));
	char **my_stdin = malloc(sizeof(char**));

	int count = 0, k = 0;
	
	op= operation_parser(operation);
		
	while( op[count] != NULL){
		if( strstr(op[count],"|") )
		{
			my_stdout[count] = NULL;//In order to use execvp() function
			break;
		}
		else
			my_stdout[count] = op[count];
		
		count++;
	}
	
	count++;

	while( op[count] != NULL)
	{	
		my_stdin[k] = op[count];
		k++;
		count++;
	}
	my_stdin[count] = NULL;//In order to use execvp() function
	
	execute_pipe(my_stdout,my_stdin);
}


