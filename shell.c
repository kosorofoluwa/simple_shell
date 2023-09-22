#include "shell.h"

int main(int ac, char *av[], char *env[])
{
	char **str = NULL;
	char *buffer = NULL, *prompt = "#C is fun$ ", *check = NULL, **temp;
	size_t len = 0;
	int inbuilt = 0, path = 4;
	ssize_t argv;

	if (ac > 1)
		av[1] = NULL;
	while (1)
	{
		if (isatty(0))
			_printf(prompt);

		argv = getline(&buffer, &len, stdin);
		if (argv == -1)
		{
			free(buffer);
			if (check != NULL)
			{
				free(check);
			}
			temp = str;
			if (str != NULL)
			{
				while (*temp)
				{
					free(temp);
					temp++;
				}
				free(str);
			}
			exit(0);
		}
		if (*buffer != '\n')
		{
			str = _strtok(buffer);
			if (strcmp("exit", str[0]) == 0)
			{
				break;
			}
			inbuilt = _builtin(str[0]);
			check = _filecheck(str[0]);
			if (inbuilt == 0 && check != NULL)
			{
				str[0] = check;
			}
			path = findpath(str[0]);
			if (path == 1)
			{
				_fork(str, env);
			}
			if (check == NULL && path == 0 && inbuilt == 0)
			{
				_printf("No such file or directory\n");
			}
		}

	}
	free(buffer);
	if (check != NULL)
	{
		free(check);
	}
	temp = str;
	if (str != NULL)
	{
		while (*temp)
		{
			free(*temp);
			temp++;
		}
		free(str);
	}
	
	exit(0);

	/*return (0);*/
}
