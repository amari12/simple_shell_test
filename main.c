#include "main.h"

/**
 * main - main funtion / entry poin
 * Return: int
 */

int main(int argc, char **argv)
{
	/*show prompt*/
	prompt();

	return (1);
}

/**
 * prompt - command prompt loop
 * 
 * shows prompt
 * waits for command to be entered
 * processes command (separates into command and argument)
 * exe command
 * shows prompt again
 *
 * Return: void
 */

void prompt()
{
	char *input, *arguments, *command;
	int exit = 0; /* = 1 when it has to exit loop*/

	while (exit != 1)
	{
		printf("our shell>> "); /*show and wait for input*/
		input = get_input(); /*saves input as string in input*/
		separate_input(input, arguments, command); /*separate input into arguments and command*/
		exit = exe_command(command, arguments); /*exe command */
		free(input); /*avoid memory leaks*/
		free(arguments);
		free(command);
	}
} /*prompt*/

