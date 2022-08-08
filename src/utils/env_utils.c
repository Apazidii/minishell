#include "minishell.h"

char *find_in_env(t_list *env, char *key)
{
	t_dict *c;
	int 	l;

	l = ft_strlen(key);
	while (env)
	{
		c = (t_dict *)env->content;
		if (ft_strncmp(c->key, key, l) == 0)
			return (c->value);
		env = env->next;
	}
	return (NULL);
}

int	insert_var(char **str, t_list *env)
{

}