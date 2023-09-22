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

