#include "minishell.h"
#include "pre_action.h"

int chech_builtin(t_group *group, t_base *base)
{
	if (ft_strncmp(group->arg_str[0], "echo", 5) == 0)
		return (echo(group->arg_str, group->number_arg));
	if (ft_strncmp(group->arg_str[0], "pwd", 6) == 0)
		return (pwd(base));
	if (ft_strncmp(group->arg_str[0], "cd", 3) == 0)
		return (cd(group->arg_str, group->number_arg));
	if (ft_strncmp(group->arg_str[0], "exit", 5) == 0)
		return (builtint_exit(base));
	if (ft_strncmp(group->arg_str[0], "export", 7) == 0)
		return (export(group->arg_str, group->number_arg, base));
	if (ft_strncmp(group->arg_str[0], "unset", 6) == 0)
		return (unset(group->arg_str, group->number_arg, base));
	if (ft_strncmp(group->arg_str[0], "env", 4) == 0)
		return (env(base));

	return (NOT_FOUND);



}