#include "shell.h"

int findpath(char *str)
{
	char *tp = "/bin/", *ref, *i;
	int n = 0, p = 0;

	ref = malloc(sizeof(char) * 50);
	if (ref == NULL)
		return(0);
	while (tp[n] != '\0')
	{
		if (tp[n] != str[n])
		{
			free(ref);
			return (0);
		}
		n++;
	}
	while (str[n] != '\0')
	{
		ref[p] = str[n];
		p++;
		n++;
	}
	ref[p] = '\0';
	i = _filecheck(ref);
	if (i != NULL)
	{
		free(ref);
		return (1);
	}
	return (0);
}
