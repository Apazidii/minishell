#include "minishell.h"
#include "pre_action.h"

int kill_pid(t_base *base)
{
	int l;
	int i;

	l = ft_lstsize(base->groups);
	i = 0;
	while (i < l)
	{
		if (base->pid[i] != 0)
			kill(base->pid[i], SIGKILL);
		i++;
	}
	if (errno == 3)
		errno = 0;
	return (1);
}

int is_builtin(t_group *group)
{
	if ((ft_strncmp(group->arg_str[0], "cd", 3) == 0		|| \
		ft_strncmp(group->arg_str[0], "echo", 5) == 0		|| \
		ft_strncmp(group->arg_str[0], "pwd", 4) == 0		|| \
		ft_strncmp(group->arg_str[0], "export", 7) == 0	|| \
		ft_strncmp(group->arg_str[0], "unset", 6) == 0		|| \
		ft_strncmp(group->arg_str[0], "env", 4) == 0		|| \
		ft_strncmp(group->arg_str[0], "exit", 5) == 0))
		return (1);
	return (0);
}