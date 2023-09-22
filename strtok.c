#include "shell.h"

char **_strtok(char *str)
{
	char **token, *toks;
	int i = 0, j = 0;

	token = malloc(10 * sizeof(char*));
	if (token == NULL)
	{
		perror("Error");
		exit(1);
	}
	toks = strtok(str, " ");
	while (toks != NULL)
	{
		while (toks[j])
		{
			if (toks[j] == '\n')
				toks[j] = '\0';
			j++;
		}
		token[i] = toks;
		i++;
		j = 0;
		toks = strtok(NULL, " ");
	}
	token[i] = NULL;
	return (token);
}
