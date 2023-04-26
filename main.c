#include "shell.h"

/**
 * main - Entry point for the shell program
 * Return: Always 0
 */
int main(void)
{
	char *args[MAX_ARGUMENTS], *filepath, *buffer = NULL, *envp[1024];
	size_t buf_size;
	pid_t pid;
	int run_flag = 1, num_chars;

	while (run_flag)
	{
		printf("$ ");
		num_chars = getline(&buffer, &buf_size, stdin);
		if (num_chars == -1)
			break;
		token_command(buffer, args);
		if (strcmp(args[0], "exit"))
		{
			run_flag = 0;
			break;
		}
		if (strcmp(args[0], "env") == 0)
		{
			char **env = environ;

			while (*env != NULL)
			{
				printf("%s\n", *env);
				env++;
			}
			break;
		}
		filepath = search_path(args[0]);
		if (filepath == NULL)
		{
			printf("Error: command not found\n");
			break;
		}
		pid = fork();
		if (pid < 0)
		{
			printf("Fork failed\n");
			exit(1);
		}
		else if (pid == 0)
		{
			envp[0] = NULL;
			execve(filepath, args, envp);
			printf("Error: command not found\n");
			exit(1);
		}
		else
		{
			wait(NULL);
		}
	}
	free(buffer);

	return (0);
}
