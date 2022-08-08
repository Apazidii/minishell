#include "minishell.h"
#include "pre_action.h"

int run_command(t_group *group, t_base *base)
{
	int error_code;


	//redirect
	if (arg_in_arr_str(group) != SUCCES)
		return (MALLOC_ERROR);
	error_code = chech_builtin(group, base);
	if (error_code == NOT_FOUND)
		error_code = run_exec(base, group->program, group->arg_str);
	if (error_code != SUCCES)
		return (EXEC_ERROR);
	return (SUCCES);
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
		if (error_code != SUCCES)
			exit(1);
		exit(0);
	}
	else
		return (SUCCES);
}