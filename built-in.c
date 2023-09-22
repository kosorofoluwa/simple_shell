#include "shell.h"

/**
 * builtin - implements built in functions
 * @str: argument count
 *
 * Return: Always 0
 */
int _builtin(char *str)
{
	char *arg[3], *un;
	int i = 0;

	if (arg == NULL)
	{
		return (0);
	}
	
	arg[0]="cd";
	arg[1]="exit";
	arg[2]="hello";

	while (i < 3 && strcmp(arg[i], str) != 0)
	{
		i++;
	}
	switch (i)
	{
		case 0:
			if (chdir(str) != 0)
			{
				perror("cd");
			}
			return (1);
		case 1:
			_printf("closing");
			exit(0);
		case 2:
			{
				un = getenv("HOSTNAME");
				if(un != NULL)
				{
					_printf(un);
				}
				else
				{
					_printf("Hostname not found");
				}
			}
			return (1);

		default:
			return (0);
	}
}
