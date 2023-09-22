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
