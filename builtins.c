#include "main.h"

/*list of builtin commaneds, and their functions*/
/*global variables - maybe move to main.h*/
/*char *bi_cmds = {"cd", "help", "exit"};*/
/*int (*bi_functions[])(char **) = {&ss_cd, &ss_help, &ss_exit};*/
/*ss = simple shell*/
/*bi = builtin*/

/*==========================================================*/
/**
 * get_nr_bi - returns number of builtin functions
 * Return: int
 */

int get_nr_bi()
{
	int nr;

	nr = sizeof(bi_cmds) / sizeof(char *);
	return (nr);
} /*get nr bi*/

/*==========================================================*/
/**
 * ss_cd - changes directory
 * @command: command
 * @arguments: args
 * Return: int
 */

int ss_cd(char *command __attribute__((unused)), char *arguments)
{
	int result;
	if (arguments[0] == NULL) /*does not have an argument*/
		fprintf(stderr, "Shell: cd expects an argument\n");
	else
	{
		result = chdir(arguments[1]);
		if (result != 0)
			perror("Shell error");
	}
	return (1);
}

/*==========================================================*/
/**
 * ss_help - shows help page
 * @command: command
 * @arguments: args
 * Return: int
 */

int ss_help(char *command __attribute__((unused)), char *arguments)
{
	int i, nr;

	nr = get_nr_bi();
	printf("Welcome to the help page!");
	printf("When the shell is ready, you will see a prompt.\n");
	printf("You can then enter a command and parameters.\n");
	printf("Some builtin commands include:\n");
	for (i = 0; i < nr; i++)
	{
		printf("\t%s\n", bi_cmds[i]);
	}
	return (1);
}

/*==========================================================*/
/**
 * ss_exit - exit shell
 * @command: command
 * @arguments: args
 * Return: int
 */

int ss_exit(char *command __attribute__((unused)), char *arguments __attribute__((unused)))
{
	return (0);
}
/*==========================================================*/

