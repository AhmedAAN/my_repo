#include "shell.h"
/**
 * check_exit - check if the command is exit
 * @args: the arguments array
 * @run_flag: a pointer to the run flag
 */
void check_exit(char **args, int *run_flag)
{
	if (strcmp(args[0], "exit") == 0)
	{
		*run_flag = 0;
	}
}

/**
 * check_env - prints environment variables
 * @args: the commands array
 */
void check_env(char **args)
{
	if (strcmp(args[0], "env") == 0)
	{
		char **env = environ;

		while (*env != NULL)
		{
			printf("%s\n", *env);
			env++;
		}
	}
}

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
		check_exit(args, &run_flag);
		check_env(args);
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
