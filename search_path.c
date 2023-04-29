#include "shell.h"
#include <limits.h>

/**
 * search_path - Search for an executable file in the directories
 * specified by PATH
 * @command: The name of the file to search for
 * Return: A pointer to a string containing the path to the file,
 * or NULL if the file was not found
 */
char *search_path(char *command)
{
	char *path;
	char *path_copy;
	char *path_dir;
	char *executable_path = NULL;
	char *temp_path;

	path = getenv("PATH");
	path_copy = strdup(path);
	path_dir = strtok(path_copy, ":");

	while (path_dir != NULL)
	{
		temp_path = malloc(PATH_MAX);
		snprintf(temp_path, PATH_MAX, "%s/%s", path_dir, command);

		if (access(temp_path, X_OK) == 0)
		{
			executable_path = temp_path;
			break;
		}
		free(temp_path);
		path_dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (executable_path);
}
