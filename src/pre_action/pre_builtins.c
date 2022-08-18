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
	if (ft_strncmp(group->program, "export", 7) == 0)
		return (export(group->arg_str, group->number_arg, base));
	if (ft_strncmp(group->program, "unset", 6) == 0)
		return (unset(group->arg_str, group->number_arg, base));
	if (ft_strncmp(group->program, "env", 4) == 0)
		return (env(base));

	return (NOT_FOUND);



}