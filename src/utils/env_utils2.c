#include "minishell.h"

t_dict *find_dict_in_env(t_list *env, char *key)
{
	t_dict *c;
	int 	l;

	l = ft_strlen(key);
	while (env)
	{
		c = (t_dict *)env->content;
		if (ft_strncmp(c->key, key, l) == 0)
			return (c);
		env = env->next;
	}
	return (NULL);
}
