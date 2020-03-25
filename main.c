#include "queue.h"
#include "build_in_commands.h"
#include "system_commands.h"

int main(int argc, char **argv)
{	 	
	
   char *operation = malloc(sizeof(char*));

   while(1)
   {
	char cwd[PATH_MAX];
	getcwd(cwd, sizeof(cwd));
	printf("%s>",cwd);
	scanf("%[^\n]s",operation);		
	getchar();
	enqueue(operation);
	
	if(is_build_in_command(operation))
	{
	    execute_command(operation);
	}
	else if(is_background_process(operation))
	{
  	    background_execution(operation);
	}
	else
	{
  	    execute_process(operation);
	}
        fflush(stdin);
   }
	
   return 0;
}
