#include "shell.h"

char *_filecheck(char *str)
{
	DIR *dir = opendir("/bin/");
	char *t, *c = NULL;
	struct dirent *entity;
	size_t len;

	if (dir == NULL)
	{
		perror("opendir");
		return NULL;
	}
	entity = readdir(dir);

	while (entity != NULL)
	{
		t = entity->d_name;
		if (strcmp(t, str) == 0)
		{
			len = strlen("/bin/") + strlen(str) + 1;
			c = (char *) malloc(len);
			if (c == NULL)
			{
				perror("malloc");
				closedir(dir);
				return NULL;
			}
			strcpy(c, "/bin/");
			strcat(c, str);
			closedir(dir);
			return c;
		}
		entity = readdir(dir);
	}
	closedir(dir);
	return (NULL);
}
