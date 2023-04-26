#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define MAX_COMMAND_LENGTH 1000
#define MAX_ARGUMENTS 100

extern char **environ;

int main(void);
int token_command(char *buffer, char **args);
char *search_path(char *filename);
void check_exit(char **args, int *run_flag);
void check_env(char **args);

char *_strtok(char *str, char *delim);
char *_strncat(char *dest, char *src, int n);
char *_strncpy(char *dest, char *src, int n);
char *_strchr(char *s, char c);
int is_delim(char c, char *delim);

#endif
