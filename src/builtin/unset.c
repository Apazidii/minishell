#include "minishell.h"
#include "builtin.h"


void delete_dict_elem(t_list **start, char *key)
{
	t_list *temp;
	t_list *list;

	list = *start;
	if (ft_strncmp(((t_dict *)list->content)->key, key, ft_strlen(key) + 1) == 0)
	{
		*start = (*start)->next;
		ft_lstdelone(list, free_dict);
		return;
	}
	while (list->next != NULL && \
			ft_strncmp(((t_dict *)list->next->content)->key, key, ft_strlen(key) + 1) != 0)
		list = list->next;
	if (list->next == NULL)
		return;
	temp = list->next;
	list->next = list->next->next;
	ft_lstdelone(temp, free_dict);
}

int unset(char **arg, int num_arg, t_base *base)
{
	int i;

	i = 0;
	while (i < num_arg)
	{
		delete_dict_elem(&(base->env_lst), arg[i]);
		i++;
	}
}