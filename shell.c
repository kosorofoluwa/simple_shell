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

/**
 * _which - Find the full path of a command in the PATH environment variable.
 * @env: An array of environment variables.
 * @command: The command to search for.
 *
 * Return: The full path of the command if found, or NULL if not found.
 */
char *_which(char **env, char *command)
{
	unsigned int i = 0;
	char **paths = NULL, *buffer = NULL;
	char *paths_copy;
	size_t length = 0;
	struct stat statbuf;

	while (env[i] != NULL)
	{
		if (strncmp(env[i], "PATH", 4) == 0)
			break;
		i++;
	}

	paths_copy = strdup(env[i]);
	paths = mystrtok(":=", paths_copy);
	free(paths_copy);

	if (paths)
	{
		for (i = 0; paths[i]; i++)
		{
			length = strlen(paths[i]) + strlen(command) + 2;
			buffer = malloc(length);
			if (buffer)
			{
				strcpy(buffer, paths[i]);
				strcat(buffer, "/");
				strcat(buffer, command);

				if (stat(buffer, &statbuf) == 0)
				{
					while (paths[i])
						free(paths[i++]);
					free(paths);
					return (buffer);
				}
				free(buffer);
				free(paths[i]);
			}
		}
		free(paths);
	}
	return (NULL);
}

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
