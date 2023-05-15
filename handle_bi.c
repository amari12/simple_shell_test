#include "main.h"

int handle_builtins(char *args[])
{
	extern char **environ;
	char **env;

	int check = 0;

	if (strcmp(args[0], "exit") == 0)
	{
		exit(EXIT_SUCCESS);
	}
	else if (strcmp(args[0], "env") == 0)
	{
		env = environ;
		while (*env)
		{
			printf("%s\n", *env);
			env++;
		}
		/*instead of conitnue*/
		check = 1;
	}
	return (check);
}

