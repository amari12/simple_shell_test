#include "main.h"
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>

/*====================================================================*/
/**
 * get_input - get input from user
 * Return: char * (input as stirng pointer)
 */

char *get_input()
{
	int size = 0; /*getline assigns size*/
	char *text = NULL; /*getline will assign text*/
	int nr_chars;

	nr_chars = getline(text, size, stdin); /*built in function*/
	if (nr_chars == -1)
	{
		if (feof(stdin)) /*end of input reached*/
			exit(WEXITSTATUS(EXIT_SUCCESS)); /* EOF / end of file */
		else
		{ /*other error*/
			perror("Unable to get line");
			exit(WEXITSTATUS(EXIT_FAILURE));
		} /*else*/
	} /*if*/
	return (text); /*successfully read line*/
} /*get input*/

/*====================================================================*/
/**
 * separate_input - separates input string as command and arguments
 * @input: input string
 * @arguments: arguments
 * @command: command to execute
 * Return: void
 */

void separate_input(char *input, char *arguments, char *command)
{
	int size = 64, i = 0, check = 0, n;
	char *deliminator = " ";
	char **args;
	char *cmd;
	char *str;
       
	strcpy(str, input); /*copy string bc strtok alters string*/

	args = malloc(sizeof(char *) * size);
	cmd = malloc(sizeof(char *));
	if (args == NULL || cmd == NULL) /*check if memory assignment successful*/
	{
		perror("Unable to allocate memory");
		exit(EXIT_FAILURE);
	}
	/*get cmd and args via strtok() */
	cmd = strtok(str, deliminator); /*returns first token*/
	while (check != 1)
	{
		args[i] = strtok(NULL, deliminator); /*NULL to continue with same string without the prev tokens*/
		if (args[i] == NULL)
			check = 1; /*stop loop*/
	}
	/*assign arguments and command*/
	command = cmd;
	for (n = 0; n <= i; n++)
	{ /* i is nr of arguments */
		arguments[n] = args[n];
	}
} /*separate input*/

/*====================================================================*/
/**
 * exe_command - executes command
 * @command: command
 * @arguments: arguments
 * Return: int (1 = exit loop, 0 continue loop)
 */

int exe_command(char *command, char *arguments)
{
	int i, nr;

	if (command == NULL)
	{ /*no command was entered*/
		return (1);
	}
	nr = get_nr_bi();
	for (i = 0; i < nr; i++)
	{ /*checks if command matches a builtin function*/
		if (strcmp(command, bi_cmds[i]) == 0) /*match found*/
			return ((*bi_functions[i])(command, arguments)); /*execute bi function*/
	}
	/*if command does not match bi func, launch the process via forking*/
	return (forking(command, arguments));
}

/*====================================================================*/
/**
 * forking - forks process into parent and child
 * @command: command
 * @arguments: arguments
 * Return: int (1)
 */

int forking(char *command, char *arguments)
{
	pid_t child_pid, wait_pid; /*process id*/
	int status, exe; /*used to check child process status*/

	child_pid = fork(); /*creates child process*/
	
	if (child_pid == 0)
	{ /*represents child process */
		exe = execvp(command, arguments); /*executes command and returns -1 if error*/
		if (exe == -1)
		{
			perror("Shell error");
			/*exit(EXIT_FAILURE);*/
		}
		exit(EXIT_FAILURE); /*exit child process*/
	} /*if child process*/
	else if (child_pid < 0)
	{
		perror("Shell error"); /*error during forking process*/
	}
	else
	{ /*current process = parent process*/
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
		{
			wait_pid = waitpid(child_pid, &status, WUNTRACED);
			if (wait_pid == -1)
			{
				perror("Shell error");
				exit(EXIT_FAILURE);
			}
		}
	} /*else*/
	return (1);
} /*forking*/

/*====================================================================*/

