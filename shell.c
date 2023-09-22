#include "shell.h"

/**
 * main - Entry point of the program
 *
 * @ac: argument count (unused)
 * @av: argument vector
 * @environ: environment variables
 *
 * Return: 0 on successful completion
 */
int main(int ac, char **av, char **environ)
{
	char *prompt = "simple_shell$ ", *full_path = NULL;
	int i, EXITVALUE;
	char **argv = NULL;
	bool interactive = isatty(fileno(stdin));
	struct stat statbuf;

	(void) ac;
	/* The SIGINT signal handler to handle Ctrl+C interrupts */
	signal(SIGINT, sigintHandler);
	while (1)
	{
		if (interactive)
		{
			i = 0;
			while (prompt[i])
				_putchar(prompt[i++]);
		}
		_mygetline();
		argv = mystrtok(" ", lineptr);
		if (argv != NULL)
		{
			if (strcmp(argv[0], "exit") == 0)
			{
				if (argv[1] != NULL)
				{
					if (atoi(argv[1]) > 0)
					{
						EXITVALUE = atoi(argv[1]), free_argv(argv), exit(EXITVALUE);
					}
					else
					{
						fprintf(stderr, "%s: 1: exit: Illegal number: %s\n", av[0], argv[1]);
						free_argv(argv), exit(2);
					}
				}
				free_argv(argv), exit(EXITSTATUS);
			}
			else if (strcmp(argv[0], "env") == 0)
				print_env(environ);
			else
			{
				if (stat(argv[0], &statbuf) == 0)
    					_myfork(argv, av, environ);
				else
				{
    					full_path = _which(environ, argv[0]);
    					if (full_path != NULL)
    					{
        					free(argv[0]);
        					argv[0] = full_path;
        					_myfork(argv, av, environ);
    					}
    					else
        					perror(av[0]);
				}
			}
			free_argv(argv);
		}
	}
	return (0);
}
