#include "shell.h"

/**
 * _strtok - tokenizes a string based on a delimiter
 * and returns an array of strings.
 * @str: the input string to tokenize.
 * @delim: the delimiter to use for tokenization.
 * Return: An array of strings containing each token from the input string,
 * or NULL if there was an error.
 */
char *_strtok(char *str, char *delim)
{
	static char *next_token;
	int i, j;
	char *token;

	if (str != NULL)
		next_token = str;

	if (next_token == NULL || *next_token == '\0')
		return (NULL);

	token = next_token;
	for (i = 0; next_token[i] != '\0'; i++)
	{
		if (!is_delim(next_token[i], delim))
		{
			for (j = i; next_token[j] != '\0'; j++)
			{
				if (is_delim(next_token[j], delim))
				{
					next_token = &next_token[j + 1];
					next_token[-1] = '\0';
					return (token);
				}
			}
			next_token = &next_token[j];
			return (token);
		}
	}
	return (NULL);
}
