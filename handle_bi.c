#include "main.h"

/**
 * handle_builtins - handles builtin functions
 * @args: input string separated into arguments
 * @environ: environmental variables
 * Return: int (check to flag if env was called)
 */

int handle_builtins(char *args[], char **environ)
{
	/*extern char **environ;*/
	char **env;
	int check = 0;
	size_t len;
	int status;

	if (strcmp(args[0], "exit") == 0)
	{
		if (args[1] != NULL)
			status = atoi(args[1]); /*will save as status in main*/
		else
			status = EXIT_SUCCESS;
		exit(status);
		/*exit(EXIT_SUCCESS);*/
	}
	else if (strcmp(args[0], "env") == 0)
	{
		env = environ;
		len = strlen(*env);
		while (*env)
		{
			/*printf("%s\n", *env);*/
			write(STDOUT_FILENO, *env, len);
			write(STDOUT_FILENO, "\n", 1);
			env++;
		}
		/*instead of conitnue*/
		check = 1;
	}
	else if (strcmp(args[0], "cd") == 0)
	{
		change_dir(args);
		check = 1;
	}
	return (check);
}

/**
 * change_dir - cd builtin
 * @args: input arguments
 * Return: void
 */

void change_dir(char *args[])
{
	char *home, *prev, *get_result, *change;
	char current[SIZE];
	int result;

	home = getenv("HOME"); /*assign variables*/
	prev = getenv("PWD");
	/*printf("prev: %s\n", prev);*/

	if (args[1] == NULL || strcmp(args[1], "~") == 0)
		change = home;
	else if (strcmp(args[1], "-") == 0)
		change = prev;
	else
		change = args[1];

	if (change == NULL)
	{
		perror("No directory found");
		return;
	}
	/*printf("Change to dir: %s\n", change);*/
	result = chdir(change); /*change directory*/
	if (result != 0)
	{
		perror("cd failed");
		return;
	}
	/*update env var (PWD) with current dir*/
	get_result = getcwd(current, sizeof(current));
	if (get_result != NULL)
		setenv("PWD", current, 1);
	else
		perror("Failed to update current directory");
	/*printf("current dir: %s\n", current);*/
}

