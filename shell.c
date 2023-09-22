#include "shell.h"

/**
 * sigintHandler - Handles the SIGINT signal (Ctrl+C)
 * @sig: The signal number (not used in the function)
 *
 * Frees the dynamically allocated memory for 'lineptr' and
 * terminates the program.
 */
void sigintHandler(int sig)
{
	(void) sig;
	free(lineptr),
	lineptr = NULL;
	_putchar('\n');
	exit(0);
}

/**
 * _mygetline - Reads a line of input from stdin
 *
 * Reads a line of input from stdin and stores it in the 'lineptr' variable
 * Dynamically allocates memory for 'lineptr' to accommodate the input line
 */
void _mygetline(void)
{
	size_t n = 0;
	ssize_t nread;

	nread = getline(&lineptr, &n, stdin);
	if (nread == -1)
	{
		free(lineptr);
		lineptr = NULL;
		exit(0);
	}

	lineptr[nread - 1] = '\0';
}

/**
 * mystrtok - tokenizes a line
 * @delim: delimiter to use
 * @line: line to tokenize
 *
 * Return: array of token, else NULL
 */
char **mystrtok(const char *delim, char *line)
{
	char *token = NULL;
	char **tokens = malloc(sizeof(char *) * 1024);
	int i = 0;

	if (!tokens)
		return (NULL);

	token = strtok(line, delim);
	if (token == NULL)
	{
		free(tokens), token = NULL;
		free(line), line = NULL;
		return (NULL);
	}

	while (token)
	{
		tokens[i] = strdup(token);
		token = strtok(NULL, delim);
		i++;
	}

	tokens[i] = NULL;
	return (tokens);
}

/**
 * _myfork - Function to create a child process and execute a specified program.
 *
 * @argv: Array of strings containing the arguments to be passed to the
 * program.
 * @av: Array of strings containing the program name and arguments.
 * @environ: Environment variables
 **/
void _myfork(char **argv, char **av, char **environ)
{
	pid_t child_pid;
	int status, exit_status;

	child_pid = fork();
	if (child_pid == -1)
		return;
	else if (child_pid == 0)
	{
		if (execve(argv[0], argv, environ) == -1)
			perror(av[0]);
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
		{
			exit_status = WEXITSTATUS(status);
			if (exit_status != 0)
			{
				EXITSTATUS = 2;
			}
		}
	}
}

