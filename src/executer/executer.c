#include "minishell.h"
#include "executer.h"

int executer(t_group *group)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		printf("Fork failed\n");
		return (FORK_ERROR);
	}
}
