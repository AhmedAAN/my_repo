#include "shell.h"

int main(void)
{
	char *buffer = NULL;
	char *args[max_args];
	size_t buf_size;
	pid_t pid;
	int run_flag = 1, num_args, num_chars;

	while (run_flag)
	{
		printf("$ ");

		/* read input from user */
		num_chars = getline(&buffer, &buf_size, stdin);
		if (num_chars == -1)
			break;

		/* make the command into tokens */
		num_args = token_command(buffer, args);

		/* chack for exit command */
		if (strcmp(args[0], "exit"))
		{
			run_flag = 0;
			break;
		}

		/* fork a new process to execute command */
		pid = fork();
		if (pid < 0)
		{
			printf("Fork failed\n");
			exit(1);
		}
		else if (pid == 0)
		{
			/* child */
			if (execvp(args[0], args) == -1)
			{
				printf("Command not found\n");
				exit(1);
			}
		}
		else
		{
			/* parent */
			wait(NULL);
		}
	}
	free(buffer);

	return (0);
}
