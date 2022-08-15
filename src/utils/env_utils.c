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

char *find_in_l_env(t_list *env, char *key, int l)
{
	t_dict *c;

	while (env)
	{
		c = (t_dict *)env->content;
		if (ft_strncmp(c->key, key, l) == 0)
			return (c->value);
		env = env->next;
	}
	return (NULL);
}

int len_key(char *s)
{
	int i;

	i = 0;
	while (ft_isalnum(s[i]) || s[i] == '_')
		i++;
	return (i);
}

char *get_value(char *s, t_list *env)
{
	int l;

	l = len_key(s);
	return (find_in_l_env(env, s, l));
}




int	insert_var(char **str, t_list *env)
{
	return (SUCCES);
}