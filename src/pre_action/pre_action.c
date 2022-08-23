#include "minishell.h"
#include "pre_action.h"

int	arg_in_arr_str(t_group *group, t_list *env)
{
	int	i;

	group->arg_str = (char **)ft_calloc(sizeof(char *), group->number_arg + 1);
	if (group->arg_str == NULL)
	{
		return (MALLOC_ERROR);
	}
	i = 0;
	while (i < group->number_arg)
	{
		group->arg_str[i] = group->arg[i].arg;
		if (group->arg[i].rep_var == 1)
			if (insert_var(&(group->arg_str[i]), env) != SUCCES)
				return (MALLOC_ERROR);
		i++;
	}
	group->arg_str[i] = NULL;
	return (SUCCES);
}

int	pre_action(t_base *base)
{
	int		error_code;
	int		status;
	t_group	*group;
	t_list	*all_groups;
	int		i;
	int		l;

	all_groups = base->groups;
	l = ft_lstsize(all_groups);
	base->pid = ft_calloc(sizeof (pid_t), l);
	if (base->pid == NULL)
		return (MALLOC_ERROR);
	i = 0;
	while (all_groups)
	{
		group = (t_group *)all_groups->content;
		error_code = arg_in_arr_str(all_groups->content, base->env_lst);
		if (error_code != SUCCES)
			return (error_code);
		if (init_pipe(all_groups, all_groups->next, base) != SUCCES)
			return (PIPE_ERROR);
		error_code = replace_fd_group(all_groups->content);
		if (error_code != SUCCES && kill_pid(base) && free_one(base->pid))
			return (error_code);
		error_code = redirect(all_groups->content, base->env_lst);
		if (error_code != SUCCES && kill_pid(base) && free_one(base->pid))
			return (error_code);
		if (l == 1 && is_builtin(all_groups->content))
		{
			error_code = run_command(all_groups->content, base);
			return_fd_group(group);
			free(base->pid);
			return (error_code);
		}
		set_fork_signals();
		error_code = apply_fork(group, base, i);
		return_fd_group(group);
		if (error_code != SUCCES && kill_pid(base) && free_one(base->pid))
			return (error_code);
		all_groups = all_groups->next;
		i++;
	}
	while (i)
	{
		waitpid(base->pid[--i], &status, 0);
		if (WEXITSTATUS(status) != SUCCES && kill_pid(base)
			&& free_one(base->pid))
			return (WEXITSTATUS(status));
	}
	free_one(base->pid);
	return (SUCCES);
}
