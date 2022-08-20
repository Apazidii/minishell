#include "minishell.h"
#include "pre_action.h"


int run_command(t_group *group, t_base *base)
{
	int error_code;

	close_unused_fd(group);

//	error_code = redirect(group, base->env_lst);
//	if (error_code == SUCCES)
//	error_code = arg_in_arr_str(group, base->env_lst);
//		if (error_code == SUCCES)
	error_code = chech_builtin(group, base);
	if (error_code == NOT_FOUND)
		error_code = run_exec(base, group->arg_str[0], group->arg_str);

	return (error_code);
}


int apply_fork(t_group *group, t_base *base, int i)
{
	int error_code;

	base->pid[i] = fork();
	if (base->pid[i] == -1)
	{
		printf("Fork failed\n");
		return (FORK_ERROR);
	}
	if (base->pid[i] == 0)
	{
		error_code = run_command(group, base);
		exit(error_code);
	}
	else
		return (SUCCES);
}