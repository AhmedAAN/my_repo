#include "shell.h"

/**
 * search_path - Search for an executable file in the directories
 * specified by PATH
 * @filename: The name of the file to search for
 * Return: A pointer to a string containing the path to the file,
 * or NULL if the file was not found
 */
char *search_path(char *filename)
{
	char path[MAX_COMMAND_LENGTH];
	int fd = open("/etc/environment", O_RDONLY);
	int n;
	char *newline, *path_value;
	char *directories[MAX_ARGUMENTS];
	int num_dirs;
	int i;

	if (fd < 0)
	{
		return (NULL);
	}
	while ((n = read(fd, path, MAX_COMMAND_LENGTH)) > 0)
	{
		newline = strchr(path, '\n');
		if (newline != NULL)
		{
			*newline = '\0';
		}
		if (strncmp(path, "PATH=", 5) == 0)
		{
			close(fd);
			path_value = path + 5;
			num_dirs = token_command(path_value, directories);
			for (i = 0; i < num_dirs; i++)
			{
				char filepath[MAX_COMMAND_LENGTH];

				snprintf(filepath, MAX_COMMAND_LENGTH, "%s/%s", directories[i], filename);
				if (access(filepath, X_OK) == 0)
				{
					return (strdup(filepath));
				}
			}
			break;
		}
	}
	close(fd);

	return (NULL);
}
