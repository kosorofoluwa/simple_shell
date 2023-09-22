#ifndef __SHELL_H__
#define __SHELL_H__

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <dirent.h>

int _putchar(char c);
int _printf(char *str);
int _builtin(char *str);
void _fork(char **toks, char *env[]);
int findpath(char *str);
char *_filecheck(char *str);
char **_strtok(char *str);
#endif /* SHELL_H */
