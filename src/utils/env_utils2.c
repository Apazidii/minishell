#include "minishell.h"

t_dict	*find_dict_in_env(t_list *env, char *key)
{
	t_dict	*c;
	size_t	l;

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

void	get_remaining_characters(size_t *start, size_t *i,
	char *str, char **res)
{
	if ((str)[*i] && (str)[*i] != '$')
	{
		*start = *i;
		while (!((str)[*i] == '\0' || (str)[*i] == '$'))
			(*i)++;
		*res = ft_strnconcat(*res, str, *start, *i);
	}
}

void	get_last_dollar(size_t *i, char *str, char **res)
{
	*res = ft_strnconcat(*res, str, *i, *i + 1);
	(*i)++;
}

char	*iterate_per_perem(size_t *i, size_t *start, char *str)
{
	char	*perem;

	(*i)++;
	*start = (*i);
	while (ft_isalnum((str)[*i]) || (str)[*i] == '_')
		(*i)++;
	perem = get_perem(str, *start, (*i));
	return (perem);
}

void	checks_and_init(size_t *i, char **res)
{
	*i = 0;
	*res = (char *)ft_calloc(1, 1);
}
