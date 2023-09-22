#include "shell.h"

/**
 * print_env - Print the current environment variables
 * @environ: Environment variables
 **/
void print_env(char **environ)
{
	int i = 0, j = 0;
	char *var = NULL;

	while (environ[i] != NULL)
	{
		var = environ[i];
		j = 0;

		while (var[j] != '\0')
		{
			_putchar(var[j]);
			j++;
		}
		_putchar('\n');
		i++;
	}
}
