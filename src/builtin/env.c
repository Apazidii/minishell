#include "minishell.h"
#include "builtin.h"

void print_env_without_declare(void *content)
{
	t_dict *c;

	c = (t_dict *)content;
	if (c->value != NULL)
		printf("%s=%s\n",c->key, c->value);
}



int env(t_base *base)
{
	ft_lstiter(base->env_lst, print_env_without_declare);
	return (SUCCES);
}