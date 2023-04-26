#include "shell.h"

/**
 * token_command - tokenize the command into the args array
 *
 * @buffer: a pointer to the input buffer
 * @args: a pointer to the array of arguments
 *
 * Return: the number of arguments
 */
int token_command(char *buffer, char **args)
{
	int num_args = 0;
	char *arg;

	arg = strtok(buffer, " \n");

	while (arg != NULL && num_args < MAX_ARGUMENTS - 1)
	{
		args[num_args] = arg;
		num_args++;
		arg = strtok(NULL, " \n");
	}

	args[num_args] = NULL;

	return (num_args);
}
