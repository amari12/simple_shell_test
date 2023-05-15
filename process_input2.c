#include "main.h"

void get_input(char *input)
{
	char *fgets_result;

	fgets_result = fgets(input, SIZE, stdin);
	if (fgets_result == NULL)
	{ /*reading error*/
		printf("\n");
		exit(EXIT_SUCCESS);
	}
	/*replace new line with string terminator*/
	if (input[strlen(input) - 1] == '\n')
		input[strlen(input) - 1] = '\0';
}

void split_input(char *input, char *args[])
{
	int i = 0;
	char cp_input[SIZE];

	/*make copy of input string*/	
	strcpy(cp_input, input);

	/*split input string into tokens: args*/
	args[i] = strtok(cp_input, " ");
	i++;
	do
	{
		args[i] = strtok(NULL, " ");
		i++;
	} while (args[i] != NULL);

}

