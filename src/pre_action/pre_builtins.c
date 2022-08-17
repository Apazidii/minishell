#include "minishell.h"
#include "pre_action.h"

int chech_builtin(t_group *group, t_base *base)
{
	if (ft_strncmp(group->program, "echo", 5) == 0)
		return (echo(group->arg_str, group->number_arg));
	if (ft_strncmp(group->program, "pwd", 6) == 0)
		return (pwd(base));
	if (ft_strncmp(group->program, "cd", 3) == 0)
		return (cd(group->arg_str, group->number_arg));
	if (ft_strncmp(group->program, "exit", 5) == 0)
		return (builtint_exit(base));
	return (NOT_FOUND);



}