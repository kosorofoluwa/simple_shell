#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <sys/stat.h>

char *lineptr = NULL;
int EXITSTATUS = 0;
int _putchar(char c);
void _myfork(char **argv, char **av, char **environ);
void print_env(char **environ);
void free_argv(char **argv);
void _mygetline(void);
void sigintHandler(int sig);
char **mystrtok(const char *delim, char *line);
char *_which(char **env, char *command);

#endif /* _SHELL_H_*/
