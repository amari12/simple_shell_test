#include "main.h"

/**
 * get_input - reads the input from user and saves as string
 * @input: input string
 * Return: void
 */

void get_input(char **input)
{
	ssize_t fgets_result;
	size_t size = SIZE;

	*input = NULL; /*initialise input pointer*/

	/*fgets_result = fgets(input, SIZE, stdin);*/
	fgets_result = getline(input, &size, stdin);
	if (fgets_result == -1)
	{
		if (feof(stdin))
		{ /*end of file reached*/
			write(STDOUT_FILENO, "\n", 1);
			exit(EXIT_SUCCESS);
		}
		else
		{ /*error reading input*/
			perror("Could not read input");
			exit(EXIT_FAILURE);
		}
	}

	/*replace new line with string terminator*/
	if ((*input)[strlen(*input) - 1] == '\n')
		(*input)[strlen(*input) - 1] = '\0';
} /*get input*/

/**
 * get_input2 - reads the input using fgets()
 * @input: input string
 * Return: void
 */

void get_input2(char **input)
{
	static char buffer[SIZE];
	static int index = 0;
	static int read_size = 0;
	char *temp;
	int newline_i, j;

	*input = NULL; /*initialise*/
	while (1) /*infinite loop until return called*/
	{
		if (index >= read_size) /*if buffer empty, read input*/
		{
			read_size = read(STDIN_FILENO, buffer, SIZE);
			if (read_size == 0)
			{ /*eof*/
				break; /*handled in main.c*/
			}
			else if (read_size < 0)
			{ /*error reading input*/
				perror("Error reading input");
				exit(EXIT_FAILURE);
			}
			index = 0;
		}
		for (newline_i = index; newline_i < read_size; newline_i++)
		{ /*find new line char */
			if (buffer[newline_i] == '\n')
				break; /*i shows index of new line*/
		}
		temp = realloc(*input, (newline_i - index + 1) * sizeof(char));
		if (temp == NULL)
		{
			perror("Memory allocation failed");
			exit(EXIT_FAILURE);
		}
		*input = temp;
		for (j = 0; index + j < newline_i; j++) /*add content of buffer to input*/
		{
			(*input)[j] = buffer[index + j];
		}
		(*input)[j] = '\0'; /*null terminator at end*/
		index = newline_i + 1; /*move index to next char after newline char*/
		if (newline_i < read_size)
		{
			return;
		}
		else if (newline_i == read_size && buffer[newline_i - 1] == '\n')
		{
			return;
		}
	} /*while*/
} /*get_input 2*/

/**
 * split_input - splits input string into separate arguments
 * @input: input string
 * @args: separated input string
 * Return: void
 */

void split_input(char *input, char *args[])
{
	int i = 0;
	char cp_input[SIZE + 1];
	char *check_token;

	/*make copy of input string*/
	strcpy(cp_input, input);

	/*split input string into tokens: args*/
	check_token = strtok(cp_input, " ");
	while (check_token != NULL)
	{
		args[i] = check_token;
		i++;
		check_token = strtok(NULL, " ");
	}
	args[i] = NULL; /*last string in array should be NULL*/
} /*split input*/

/**
 * forking - forks parent and child process and exe cmd
 * @input: input string
 * @args: separated input string
 * @cmd: command (args[0])
 * @path: path
 * Return: void
 */

void forking(char *input, char *args[], char *cmd, char *path)
{
	pid_t fork_result;
	char *path_temp, *directory, *full_path = NULL;
	int status;

	fork_result = fork(); /*gives a pid*/
	if (fork_result == -1) /*error*/
	{
		perror("Fork failed");
		exit(EXIT_FAILURE);
	} /*fail*/
	else if (fork_result == 0) /*success -> child process*/
	{
		path_temp = strdup(path); /*where does path come from?*/
		directory = strtok(path_temp, ":"); /*full_path = NULL;*/
		while (directory != NULL)
		{
			full_path = malloc(strlen(directory) + strlen(input) + 2);
			sprintf(full_path, "%s/%s", directory, cmd);
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
		} /*while*/
		if (full_path == NULL)
		{ /*cmd not found in path*/
			/*printf("Command not found in PATH\n");*/
			perror("Command not found in PATH");
			exit(EXIT_FAILURE);
		}
		execve(full_path, args, NULL); /*exe cmd*/
		perror("execve failed"); /*if exe fails*/
		exit(EXIT_FAILURE);
	} /*child*/
	else /*parent*/
		wait(&status);
} /*forking*/

