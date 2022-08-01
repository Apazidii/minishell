#include "minishell.h"
#include "parser.h"

int free_group_arg(t_arg *arg, int num_arg)
{
	int i;

	if (arg != NULL)
	{
		i = -1;
		while (++i < num_arg)
			if (arg[i].arg != NULL)
				free(arg[i].arg);
		free(arg);
	}
	return (1);
}


void free_group_list(void *content)
{
	free_group(content);
}

int free_group(t_group *group)
{
	if (group == NULL)
		return (1);
	if (group->program != NULL)
		free(group->program);
	if (group->redirect.redirect_file != NULL)
		free(group->redirect.redirect_file);
	if (group->reverse_redirect.redirect_file != NULL)
		free(group->reverse_redirect.redirect_file);
	if (group->number_arg > 0)
		free_group_arg(group->arg, group->number_arg);
	free(group);
	return (1);
}