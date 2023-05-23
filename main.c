#include "main.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * main - main funtion / entry poin
 * @argc: nr of arguments
 * @argv: arguments
 * Return: int
 */

int main(int argc __attribute__((unused)),
		char *argv[] __attribute__((unused)))
{
	/*char input[SIZE];*/
	char *input = NULL;
	/*int i;*/
	/*char newline = '\n';*/
	char *exit_msg = "EOF\n...\n";
	char /**arg,*/ *cmd;
	char *args[ARGS_SIZE];
	int exit_loop = 0;
	char *path; /*, *temp;*/
	int check; /*for builtin, check for env*/
	char **environ = __environ; /*global variable*/
	/*char *directory;*/

	path = getenv("PATH"); /*get path*/
	/*temp = strdup(path);*/
	/*directory = strtok(temp, ";");*/ /*initialise dir*/
	while (exit_loop != 1) /*shell loop*/
	{
		printf("our shell>> "); /*prompt*/
		fflush(stdout); /*flush output buffer*/
		/*get_input(&input);*/ /*read input*/
		get_input2(&input); /*advanced*/
		if (input == NULL)
		{ /*eof*/
			exit_loop = 1; /*will exit loop*/
			write(STDOUT_FILENO, exit_msg, strlen(exit_msg));
			/*write(STDOUT_FILENO, &newline, 1);*/
			break;
		}
		split_input(input, args); /*get args list*/
		cmd = args[0];
		/*handle builtin*/
		check = handle_builtins(args, environ);
		if (check == 1)
			continue; /*env builtin or cd*/
		/*fork - child process*/
		forking(input, args, cmd, path);
	} /*show prompt*/
	free(input);
	return (0);
}

