#include "shell.h"

/**
 * free_argv - frees an array
 *
 * @argv: array
 *
 */
void free_argv(char **argv)
{
	int i;

	for (i = 0; argv[i]; i++)
	{
		free(argv[i]), argv[i] = NULL;
	}
	free(argv), argv = NULL;
	free(lineptr);
}
