#include "shell.h"

void _fork(char **toks, char *env[])
{
	pid_t childpid;
	int status;

	childpid = fork();
	if (childpid == -1)
	{
		perror("fork unsuccessful");
		return;
	}
	if (childpid == 0)
	{
		if (execve(toks[0], toks, env) == -1)
			perror("No such file or directory");
	}
	else
	{
		wait(&status);
	}
}
