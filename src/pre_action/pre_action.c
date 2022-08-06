#include "minishell.h"
#include "pre_action.h"

int arg_in_arr_str(t_group *group)
{
	int i;

	group->arg_str = ft_calloc(sizeof(char *), group->number_arg);
	if (group->arg_str == NULL)
	{
		printf("Malloc Error");
		return (MALLOC_ERROR);
	}
	i = 0;
	while (i < group->number_arg)
	{
		group->arg_str[i] = group->arg[i].arg;
		i++;
	}
	return (SUCCES);
}

int pre_action(t_base *base)
{
	//добавить переменные среды внутрь агрументов
	t_group *group;
	t_list *all_groups;

	while (all_groups)
	{
		group = (t_group *)all_groups->content;
		if (arg_in_arr_str(group) != SUCCES)
			return (MALLOC_ERROR);
		if (chech_builtin(group, base) != SUCCES)
			return (SUCCES);
		all_groups = all_groups->next;
	}
	return (SUCCES);
}



//int parse_arg(t_group *group, t_base *base)
//{
//	char *arg;
//
//	arg = group->arg->arg;
//	while (*arg != '\0')
//	{
//		if (*arg == '$')
//
//		arg++;
//	}
//
//}
