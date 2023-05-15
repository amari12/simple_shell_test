#include "main.h"
#include <unistd.h>
#include <stdlib.h>

/**
 * main - main funtion / entry poin
 * @argc: nr of arguments
 * @argv: arguments
 * Return: int
 */

int main(int argc __attribute__((unused)),
	       	char *argv[] __attribute__((unused)))
{
	char input[SIZE];
	int i;
	/*char *arg, *cmd, *args[3];*/
	/*char *cmd = NULL;*/
	char *args[ARGS_SIZE];
	/*char *fgets_result;*/
	pid_t fork_result;
	int exit_loop = 0, status;
	char *path;
	/*extern char **environ;*/
	/*char **env;*/ /*for builtin env*/
	char *path_temp, *directory, *full_path; /*for child process*/
	int check; /*for builtin, check for env*/

	path = getenv("PATH"); /*get path*/

	while (exit_loop != 1) /*shell loop*/
	{
		printf("our shell>> "); /*prompt*/
		fflush(stdout); /*fluch output buffer*/

		get_input(input);
		/*fgets_result = fgets(input, SIZE, stdin);*/ /*get input*/
		/*if (fgets_result == NULL)*/
		/*{*/ /*reading error*/
			/*printf("\n");*/
			/*break;*/ /*show prompt again*/
			/*exit(EXIT_SUCCESS);*/
		/*}*/
		/*if (input[strlen(input) - 1] == '\n')*/ /*replace new line char*/
			/*input[strlen(input) - 1] = '\0';*/
		
		/*split cmd and arg*/
		split_input(input, args);
		/*cmd = args[0];*/
		
		/*test*/
		for (i = 0; args[i] != NULL; i++)
			printf("Input %i: %s ", i, args[i]);
		printf("\n");
		/*cmd = strtok(input, " ");*/
		/*arg = strtok(NULL, " ");*/
		
		/*handle builtin*/
		check = handle_builtins(args);
		if (check == 1)
			continue; /*env builtin*/

		/*if (strcmp(cmd, "exit") == 0)*/
		/*{*/
			/*exit(EXIT_SUCCESS);*/
		/*}*/

		/*HANDLE BUILTIN*/
		/*if (strcmp(cmd, "env") == 0)*/
		/*{*/
		/*	env = environ;*/
		/*	while (*env)*/
		/*	{*/
		/*		printf("%s\n", *env);*/
		/*		env++;*/
		/*	}*/
		/*	continue;*/
		/*}*/

		/*fork - child process*/
		fork_result = fork(); /*pid*/
		if (fork_result == 0)
		{
			/*exe command in child process*/
			/*args[0] = cmd;*/
			/*args[1] = arg;*/
			/*args[2] = NULL;*/
			/*search for command in path*/
			path_temp = strdup(path);
			directory = strtok(path_temp, ":");
			full_path = NULL;
			
			while (directory != NULL)
			{
				full_path = malloc(strlen(directory) + strlen(input) + 2);
				/*sprintf(full_path, "%s%s", directory, input);*/
				sprintf(full_path, "%s/%s", directory, input);
				if (access(full_path, X_OK) == 0)
				{
					break;
				}
				else
				{
					free(full_path);
					full_path = NULL;
				}
				directory = strtok(NULL, ":");
				/*prev: directory = strtok(path_temp, ":");*/
			}

			if (full_path == NULL)
			{ /*command not found in path*/
				printf("Command not found in PATH\n");
				exit(EXIT_FAILURE);
			}

			/*exe command*/
			execve(full_path, args, NULL);
			/*execve(cmd, args, NULL);*/

			/*if execve fails*/
			perror("execve failed");
			exit(EXIT_FAILURE);
		}
		else if (fork_result == -1) /*error*/
		{
			perror("Fork failed");
			exit(EXIT_FAILURE);
		}
		else
		{ /*parent process waiting for child to exe*/
			wait(&status);
			/*wait(NULL):*/
		} /*will loop again*/
	}
	/*show prompt*/

	return (0);
}

