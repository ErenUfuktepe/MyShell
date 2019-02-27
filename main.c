#include "queue.h"
#include "build_in_commands.h"
#include "system_commands.h"

int main(int argc, char **argv)
{	 	
	
	if(strstr(argv[0],".out") != NULL)
		remove_string(argv[0],".out");
		
	char * myshellName = parse_string(argv[0],"./");
	char *operation = malloc(sizeof(char*));
	
	strcat(myshellName,">");

	while(1)
	{
		printf("%s",myshellName);
		scanf("%[^\n]s",operation);
		getchar();
			
		enqueue(operation);
		
		if(is_build_in_command(operation))
			execute_command(operation);
			
		else if(is_background_process(operation))
			background_execution(operation);
		else
			execute_process(operation);
 	}
		
	return 0;
}
